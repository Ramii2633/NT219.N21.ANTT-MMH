#include "cryptlib.h"
#include "x509cert.h"
#include "secblock.h"
#include "filters.h"
#include "rsa.h"
#include "sha.h"
#include "hex.h"
#include "pem.h"
#include "files.h"

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>

using namespace CryptoPP;
using namespace std;
using namespace std::filesystem;

std::string toDate(const std::string& input) {
    return "20" + input.substr(0, 2) + "/" + input.substr(2, 2) + "/" + input.substr(4, 2) + " " +
        input.substr(6, 2) + ":" + input.substr(8, 2) + ":" + input.substr(10, 2);
}

void printCertInfo(const std::string& pemSer) {
    StringSource ss1(pemSer, true);
    X509Certificate cert;
    PEM_Load(ss1, cert);

    cout << "Version: " << cert.GetVersion() << endl;
    cout << "Subject identity: " << cert.GetSubjectDistinguishedName() << endl;
    cout << "Issuer: " << cert.GetIssuerDistinguishedName() << endl;
    cout << "Validity date" << endl;
    cout << "\tNot before: " << toDate(cert.GetNotBefore().EncodeValue()) << endl;
    cout << "\tNot after: " << toDate(cert.GetNotAfter().EncodeValue()) << endl;
}

bool verifyCert(const std::string& pemSer, const std::string& pemCa) {
    StringSource ss1(pemSer, true);
    X509Certificate serverCert;
    PEM_Load(ss1, serverCert);

    StringSource ss2(pemCa, true);
    X509Certificate caCert;
    PEM_Load(ss2, caCert);

    const SecByteBlock& signature = serverCert.GetCertificateSignature();
    const SecByteBlock& toBeSigned = serverCert.GetToBeSigned();
    const X509PublicKey& publicKey = caCert.GetSubjectPublicKey();

    RSASS<PKCS1v15, SHA256>::Verifier verifier(publicKey);
    return verifier.VerifyMessage(toBeSigned, toBeSigned.size(), signature, signature.size());
}

bool selfSign(const std::string& pemCertificate) {
    StringSource ss(pemCertificate, true);
    X509Certificate cert;
    PEM_Load(ss, cert);

    const SecByteBlock& signature = cert.GetCertificateSignature();
    const SecByteBlock& toBeSigned = cert.GetToBeSigned();
    const X509PublicKey& publicKey = cert.GetSubjectPublicKey();

    RSASS<PKCS1v15, SHA1>::Verifier verifier(publicKey);
    return verifier.VerifyMessage(toBeSigned, toBeSigned.size(), signature, signature.size());
}

int main(int argc, char* argv[])
{
    const string path = "D:\\Daihoc\\Nam2\\MMH\\Lab\\Lab04\\Watt";//thay các đường dẫn đến thư muc chứa chứng chỉ web
    vector<string> fileInFolder;

    for (const auto& entry : directory_iterator(path)) {
        if (!is_regular_file(entry)) {
            continue;
        }
        fileInFolder.push_back(entry.path().string());
    }

    for (size_t i = 0; i < fileInFolder.size() - 1; i++) {
        string pemServerCert, pemCaCert;

        FileSource(fileInFolder[i].c_str(), true, new StringSink(pemServerCert));
        FileSource(fileInFolder[i + 1].c_str(), true, new StringSink(pemCaCert));

        printCertInfo(pemServerCert);

        bool result = verifyCert(pemServerCert, pemCaCert);
        cout << (result ? "Verified certificate" : "Failed to verify certificate") << endl;
        cout << "-------------------------------------------------" << endl;
    }

    string pemRoot;
    FileSource(fileInFolder.back().c_str(), true, new StringSink(pemRoot));
    printCertInfo(pemRoot);

    bool result = selfSign(pemRoot);
    cout << (result ? "Verified certificate" : "Failed to verify certificate") << endl;

    return 0;
}