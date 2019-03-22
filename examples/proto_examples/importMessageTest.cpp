#include <iostream>
#include <fstream>
#include <string>
#include "msgs/addressbook.pb.h"
#include "msgs/Geometry.pb.h"
#include "msgs/Ibeo.pb.h"
#include "ibeosdk/Time.hpp"

using namespace std;
using namespace ibeosdk;

// This function fills in a Person message based on user input.
void PromptForAddress(tutorial::Person* person) {
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
  if (!email.empty()) {
    person->set_email(email);
  }

  while (true) {
    cout << "Enter a phone number (or leave blank to finish): ";
    string number;
    getline(cin, number);
    if (number.empty()) {
      break;
    }

    tutorial::Person::PhoneNumber* phone_number = person->add_phones();
    phone_number->set_number(number);

    cout << "Is this a mobile, home, or work phone? ";
    string type;
    getline(cin, type);
    if (type == "mobile") {
      phone_number->set_type(tutorial::Person::MOBILE);
    } else if (type == "home") {
      phone_number->set_type(tutorial::Person::HOME);
    } else if (type == "work") {
      phone_number->set_type(tutorial::Person::WORK);
    } else {
      cout << "Unknown phone type.  Using default." << endl;
    }
  }
}

// Main function:  Reads the entire address book from a file,
//   adds one person based on user input, then writes it back out to the same
//   file.
int main(int argc, char* argv[]) {
  // Verify that the version of the library that we linked against is

  Ibeo_msg::ObjectLuxList objects;
  objects.set_numberofobjects(5);
  NTPTime nptTime = NTPTime();
  nptTime.setFromPTime(Time::localTime());
  objects.set_timestamp(nptTime.getMilliseconds());
  for (int i=0; i<objects.numberofobjects(); i++){
    Ibeo_msg::ObjectLux *obj = objects.add_objects();
    obj->set_objectid(i*100);
    obj->set_objectage(i);
    obj->set_boundingboxwidth(i*8);
    obj->set_boundingboxlength(i*9);
    Geometry_msg::Point2d *point = obj->mutable_referencepoint();
    point->set_posx(i*5);
    point->set_posy(i*10);
  }

  std::cout << "=================objects info=================" << std::endl;
  std::cout << "*****| number of objects:" << objects.numberofobjects() << " |*****" << std::endl;
  std::cout << "*****| time stamp of this constellation: " << objects.timestamp() << " |*****" << std::endl;
  std::cout << "***************** object info ******************" << std::endl;
  for (int i=0; i<objects.numberofobjects(); i++){
    std::cout << "-----------|  " << i << "  st object |-------------" << std::endl;
    std::cout << "-----------|  object id:" << objects.objects()[i].objectid() << "   |-------------" << std::endl;
    std::cout << "-----------|  object bouding box width:" << objects.objects()[i].boundingboxwidth() << "   |-------------" << std::endl;
    std::cout << "-----------|  object bouding box length:" << objects.objects()[i].boundingboxlength() << "   |-------------" << std::endl;
    std::cout << "-----------|  object refenrencepoint x:" << objects.objects()[i].referencepoint().posx() << "   |-------------" << std::endl;
    std::cout << "-----------|  object refenrencepoint y:" << objects.objects()[i].referencepoint().posy() << "   |-------------" << std::endl;
    std::cout << "-----------------------------------------------------" <<std::endl;
  }
  

  // Optional:  Delete all global objects allocated by libprotobuf.
  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}
