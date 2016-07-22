# MRND_Json-deserializer
Program to deserialize the json objects into structs in C.

JSON format :
{
    "firstName": "Aravind",
    "lastName": "M",
    "height": 5.10,
     "age": 22,
"phoneNumbers": [
        {  "type": "home",
            "number": "212 555-1234" },
        {  "type": "fax",
            "number": "646 555-4567" }   
     ]
}  

You can get information with very intuitive queries like 
1) given firstname and lastname, get phonenumbers
2) Getting average of age of all the persons. etc
