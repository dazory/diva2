# References
1. https://www.programmersought.com/article/70796873937/
2. https://developers.google.com/protocol-buffers/docs/cpptutorial
3. https://hub1234.tistory.com/26
4. https://www.ikpil.com/1053

<br>
<br>

# Overview
## Data Serialization이란?
software에서 data serialization은 메모리를 <u>디스크에 저장</u>하거나 <u>네트워크 통신에 사용할 수 있는 형태로 변환</u>하는 것을 의미한다.

데이터의 메모리 구조는 크게 value type과 reference type으로 나뉜다. **value type**은 int, float, char와 같은 것을 의미한다. 이러한 타입의 데이터는 stack에 메모리가 쌓이므로 직접 접근이 가능하다.
반면 **reference type**은 변수 선언 시 heap에 메모리가 할당되고, stack에서는 해당 heap메모리를 <u>참조</u>하는 구조로 되어있다. 저장 및 통신에는 이러한 reference type을 사용할 수가 없는데, 그 이유는 각 PC마다 사용하는 메모리 공간 주소가 다르므로, stack에서 꺼낸 메모리주소값을 다른 PC로 보냈을 때 해당 PC에서는 전혀 엉뚱한 곳을 가리키게 때문이다. 이러한 reference type의 예로는 포인터 변수등이 있다. 

이처럼 reference type의 데이터는 저장 및 통신이 불가능하므로, data serialization과정을 통해 데이터를 text 혹은 binary형태로 변환해주어야 한다. C++에서 data serialization을 지원하는 라이브러리로는 google protocol buffer, sweet persist, s11n, boost::serialize 등이 있다. 각각의 라이브러리는 쓰임이나 장점이 다르다. diva2에서는 google protocol buffer를 사용하기로 한다.
<br><br>

## 구글 프로토콜 버퍼란?
구글에서 개발한 Serialized Data Structure 오픈소스이다. 다양한 언어를 지원한다. 선택적으로 데이터를 압축할 수도 있으며, 데이터 버전 관리를 자동으로 처리해준다는 장점이 있다. 

<br>
<br>

# 사용방법
## 1. Development Environment Setting
### 1-1. protobuf installation
```sh
sudo apt-get install autoconf automake libtool curl make g++ unzip git
git clone https://github.com/protocolbuffers/protobuf.git
cd protobuf
git submodule update --init --recursive
./autogen.sh
./configure
make
sudo make install
sudo ldconfig
protoc --version
```
result:
```sh
libprotoc 3.12.3
```

<br>
<br>

### 1-2. Using protobuf on the command line (terminal에서 아주 간단한 실습)
1-2-1. proto file을 생성
```sh
mkdir -p CSDN_ws/protobuf/teminal/
cd CSDN_ws/protobuf/teminal/
gedit AddressBook.proto
```
```proto
package tutorial;

message Person {
    required string name=1;
    required int32 id=2;
    optional string email=3;

    enum PhoneType {
        MOBILE=0;
        HOME=1;
        WORK=2;
    }

    message PhoneNumber {
        required string number=1;
        optional PhoneType type=2 [default=HOME];
    }

    repeated PhoneNumber phone=4;
}

message AddressBook {
    repeated Person person=1;
}
```
1-2-2. 위에서 만든 .proto 파일을 c++ header files로 변환
```sh
protoc --cpp_out=./ AddressBook.proto
ls
```
result: .h와 .cc파일이 생성됨을 확인할 수 있다.
```sh
AddressBook.pb.cc  AddressBook.pb.h   AddressBook.proto
```
1-2-3. header file을 이용하여 C++에서 protobuf 사용
```sh
gedit main.cpp
```
```c++
#include <iostream>
#include <fstream>
#include <vector>
#include "AddressBook.pb.h"

using namespace std;

// This function fills in a Person message based on user input.
void PromptForAddress(tutorial::Person* person) 
{
    cout << "Enter person ID number: ";
    int id;
    cin >> id;
    person->set_id(id);
    cin.ignore(256, '\n');

    cout << "Enter name: ";
    getline(cin, *person->mutable_name());

    cout << "Enter email address (blank for none): ";
    string email;
    getline(cin, email);
    if (!email.empty()) 
    {
        person->set_email(email);
    }

    while (true) 
    {
        cout << "Enter a phone number (or leave blank to finish): ";
        string number;
        getline(cin, number);
        if (number.empty()) 
        {
            break;
        }

        tutorial::Person::PhoneNumber* phone_number = person->add_phone();
        phone_number->set_number(number);

        cout << "Is this a mobile, home, or work phone? ";
        string type;
        getline(cin, type);
        if (type == "mobile") 
        {
            phone_number->set_type(tutorial::Person::MOBILE);
        } 
        else if (type == "home") 
        {
            phone_number->set_type(tutorial::Person::HOME);
        }
         else if (type == "work") 
         {
            phone_number->set_type(tutorial::Person::WORK);
        }
        else 
        {
            cout << "Unknown phone type.  Using default." << endl;
        }
    }
}


int main(int argc, char *argv[])
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;

    if (argc != 2) 
    {
        cerr << "Usage:  " << argv[0] << " ADDRESS_BOOK_FILE" << endl;
        return -1;
    }

    tutorial::AddressBook address_book;

    {
    // Read the existing address book.
    fstream input(argv[1], ios::in | ios::binary);
    if (!input) {
      cout << argv[1] << ": File not found.  Creating a new file." << endl;
    } else if (!address_book.ParseFromIstream(&input)) {
      cerr << "Failed to parse address book." << endl;
      return -1;
    }
    }

    // Add an address.
    PromptForAddress(address_book.add_person());

    {
    // Write the new address book back to disk.
    fstream output(argv[1], ios::out | ios::trunc | ios::binary);
    if (!address_book.SerializeToOstream(&output)) {
      cerr << "Failed to write address book." << endl;
      return -1;
    }
    }

    // Optional:  Delete all global objects allocated by libprotobuf.
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
```
1-2-4. main.cpp를 컴파일하여 실행하기
```sh
g++ AddressBook.pb.cc main.cpp -o main `pkg-config --cflags --libs protobuf`
ls
```
result:
```sh
AddressBook.pb.cc  AddressBook.pb.h   AddressBook.proto  main  main.cpp
```
main 실행파일 실행 (이때 입력인자로 name.txt를 입력)
```sh
./main name.txt
```
1-2-5. ID, name, email, phone number등 입력 후 종료하기

1-2-6. CSDN_ws/protobuf/terminal 폴더 들어가면 name.txt파일이 생겼음을 확인할 수 있다.

<br>

