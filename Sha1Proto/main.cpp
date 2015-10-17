#include <iostream>
#include <bitset>
#include <vector>
#include <c++/sstream>
#include "Sha1.h"

using namespace std;

/*
unsigned int Ch(unsigned int x,unsigned int y,unsigned int z){
    //uint32_t f = x & y;
    //uint32_t e = ~x & z;
    //return f^e;
    return ( x & y) ^ (~x & z);
}

unsigned int Parity(unsigned int x,unsigned int y,unsigned int z){
    return x ^ y ^ z;
}

unsigned int Maj(unsigned int x,unsigned int y,unsigned int z){
    return (x & y) ^ (x & z) ^ (y & z);
}
 */


int main() {

    Sha1 hasher;
    hasher.Hash("abc");
    cout << endl;
    cout << endl;
    Sha1 hasher1("Heipowoaidoiwond");

    /*
    string input;
    cout << endl;
    getline(cin,input);

    vector<unsigned int> bitsMessage;

    for(int i = 0;i<input.length();i++){
        bitsMessage.push_back(input[i]);
        cout << endl << bitset<8>(bitsMessage[i]);
    }


    cout << endl;
    for(auto &attack : bitsMessage){
        cout << bitset<8>(attack) << " ";
    }


    cout << endl<<"Message contains " << bitsMessage.size()*8 << " bits";


    cout << endl << "Need to add " << (448 - bitsMessage.size()*8)/8 << " byte";


    cout << endl;



    cout <<endl<< "----------"<<endl;
    cout << 448-bitsMessage.size()*8;
    cout << endl;
    cout << endl;

    //De siste 64 bits!!
    uint64_t  t = bitsMessage.size()*8;
    unsigned int t1 = (uint8_t)(t >> 56);
    unsigned int t2 = (uint8_t)(t >> 48);
    unsigned int t3 = (uint8_t)(t >> 40);
    unsigned int t4 = (uint8_t)(t >> 32);
    unsigned int t5 = (uint8_t)(t >> 24);
    unsigned int t6 = (uint8_t)(t >> 16);
    unsigned int t7 = (uint8_t)(t >> 8);
    unsigned int t8 = (uint8_t)(t);

    cout << bitset<8>(t1) << " " <<bitset<8>(t2)<< " " <<bitset<8>(t3)<< " " <<bitset<8>(t4)<< " " <<bitset<8>(t5)<< " " <<bitset<8>(t6)<< " " <<bitset<8>(t7)<< " " <<bitset<8>(t8);

    for(int i = 0; i<53;i++){
        if(i == 0){
            bitsMessage.push_back(128);
        }
        else{

            bitsMessage.push_back(0);
        }
    }


    bitsMessage.push_back(t1);
    bitsMessage.push_back(t2);
    bitsMessage.push_back(t3);
    bitsMessage.push_back(t4);
    bitsMessage.push_back(t5);
    bitsMessage.push_back(t6);
    bitsMessage.push_back(t7);
    bitsMessage.push_back(t8);

    //Adde de siste 64 bits (8 byte)

    cout << endl;

    for(auto &attack : bitsMessage){
        cout << bitset<8>(attack) << " ";
    }
    cout <<endl<< "----------"<<endl;
    cout << bitsMessage.size();
    cout << endl;

    vector<unsigned int> Words;

    for(int i = 0;i<bitsMessage.size();i = i + 4){
        Words.push_back(bitsMessage[i] << 24 | bitsMessage[i+1]<<16 | bitsMessage[i+2]<<8 | bitsMessage[i+3]);
    }

    cout << endl;
    cout << Words.size();
    cout << endl;

    for(auto &current : Words){
        cout << bitset<32>(current) << " ";
    }

    //Constants
    unsigned int K1 = 0x5a827999;
    unsigned int K2 = 0x6ed9eba1;
    unsigned int K3 = 0x8f1bbcdc;
    unsigned int K4 = 0xca62c1d6;

    unsigned int digest[5];

    //Hex
    digest[0] = 0x67452301;
    digest[1] = 0xefcdab89;
    digest[2] = 0x98badcfe;
    digest[3] = 0x10325476;
    digest[4] = 0xc3d2e1f0;


    uint32_t A = digest[0];
    uint32_t B = digest[1];
    uint32_t C = digest[2];
    uint32_t D = digest[3];
    uint32_t E = digest[4];
    uint32_t T;

    uint32_t CurrentWord;


    //Beginning of block

    for(int i = 1;i<2;i++){
        for(int t = 0;t<80;t++){
            if(t < 16){
                CurrentWord = Words[t];
                //cout << endl << t << " " << CurrentWord;
            }
            else{
                Words.push_back(((Words[t-3] ^ Words[t-8] ^ Words[t-14] ^ Words[t-16]) <<1) | ((Words[t-3] ^ Words[t-8] ^ Words[t-14] ^ Words[t-16]) >> 32-1));
                CurrentWord = Words[t];
            }

            if(t <= 19){            //Round 1
                T = ((A << 5) | (A >> 32-5)) + Ch(B,C,D) + E + K1 + CurrentWord;
            }
            else if(t > 19 && t <= 39){
                T = ((A << 5) | (A >> 32-5)) + Parity(B,C,D) + E + K2 + CurrentWord;
            }
            else if(t > 39 && t <= 59){            //Round 3
                T = ((A << 5) | (A >> 32-5)) + Maj(B,C,D) + E + K3 + CurrentWord;
            }
            else{            //Round 4
                T = ((A << 5) | (A >> 32-5)) + Parity(B,C,D) + E + K4 + CurrentWord;
            }

            E = D;
            D = C;
            C = ((B << 30) | (B >> 32-30));
            B = A;
            A = T;

        }

        digest[0] = A + digest[0];
        digest[1] = B + digest[1];
        digest[2] = C + digest[2];
        digest[3] = D + digest[3];
        digest[4] = E + digest[4];

    }

    //End of Block

    cout << "Message Digest is: "<<endl;
    //cout <<"%X\n" << digest[0] << " %X\n" <<digest[1] << " %X\n" <<digest[2] << " %X\n" <<digest[3] << " %X\n" <<digest[4];
    printf("%X",digest[0]);
    printf(" %X",digest[1]);
    printf(" %X",digest[2]);
    printf(" %X",digest[3]);
    printf(" %X",digest[4]);

    //string answer = "%X" + digest[0];

    std::stringstream sstream;
    sstream << std::hex << digest[0] << digest[1] << digest[2] << digest[3]<< digest[4];
    string answer = sstream.str();
    cout <<endl;
    cout << answer;
    */



    return 0;
}