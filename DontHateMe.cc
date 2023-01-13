#include <iostream>
#include <chrono>
#include <thread>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h>
#include <cryptopp/aes.h>
#include <cryptopp/modes.h>

// Screen coordinates and color to click on
const int X = 100;
const int Y = 100;
const int R = 255;
const int G = 0;
const int B = 0;

// AES encryption key and initialization vector
const byte KEY[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};
const byte IV[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                   0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10};

int main()
{
    // Create a CryptoPP filter to encode the task name
    CryptoPP::HexEncoder encoder;
    encoder.Attach(new CryptoPP::StringSink(encodedTaskName));

    // Create a CryptoPP AES encryptor object
    CryptoPP::AES::Encryption aesEncryptor(KEY, sizeof(KEY));
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryptor(aesEncryptor, IV);

    // Loop forever, changing the task name and encrypting memory every 5 seconds
    while (true)
    {
        // Generate a random task name
        std::string taskName = generateRandomTaskName();

        // Encode the task name using the CryptoPP filter
        encoder.Put((const byte*)taskName.data(), taskName.size());
        encoder.MessageEnd();

        // Encrypt the memory using the CryptoPP AES encryptor
        encryptMemory(cbcEncryptor);

        // Click on the specified color on the screen
        clickOnColor(X, Y, R, G, B);

        // Sleep for 5 seconds before changing the task name and encrypting memory again
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    return 0;
}