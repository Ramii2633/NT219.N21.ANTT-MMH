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
#include <string>

using namespace CryptoPP;

std::string pemSerCert;
std::string pemCaCert;


int main(int argc, char* argv[])
{
    
    FileSource pemSer("D:\\Daihoc\\Nam2\\MMH\\Lab\\Lab04\\c0.pem", true, new StringSink(pemSerCert)); 
    FileSource pemCa("D:\\Daihoc\\Nam2\\MMH\\Lab\\Lab04\\c1.pem", true, new StringSink(pemCaCert));

    //trích xuất thông tin chứng chỉ của Server
    StringSource ss1(pemSerCert, true);
    X509Certificate serverCert;
    PEM_Load(ss1, serverCert);

    //trích xuất thông tin chứng chỉ của CA
    StringSource ss2(pemCaCert, true);
    X509Certificate caCert;
    PEM_Load(ss2, caCert);

    //trích xuất các tham số cần thiết để xác thực
    const SecByteBlock& signature = serverCert.GetCertificateSignature();
    const SecByteBlock& toBeSigned = serverCert.GetToBeSigned();
    const X509PublicKey& publicKey = caCert.GetSubjectPublicKey();

    //Tạo đối tượng xác thực
    RSASS<PKCS1v15, SHA256>::Verifier verifier(publicKey);
    bool result = verifier.VerifyMessage(toBeSigned, toBeSigned.size(), signature, signature.size());

    if (result)
        std::cout << "Verified certificate (Xac thuc thanh cong!)" << std::endl;
    else
        std::cout << "Failed to verify certificate (Xac thuc khong thanh cong!)" << std::endl;
    return 0;
}
