// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <iostream>
#include <qbytearray.h>
#include <qstring.h>

void wrapInFunction()
{

//! [0]
QByteArray ba0("Hello");
//! [0]


//! [1]
QByteArray ba1;
ba1.resize(5);
ba1[0] = 0x3c;
ba1[1] = 0xb8;
ba1[2] = 0x64;
ba1[3] = 0x18;
ba1[4] = 0xca;
//! [1]


//! [2]
for (qsizetype i = 0; i < ba1.size(); ++i) {
    if (ba1.at(i) >= 'a' && ba1.at(i) <= 'f')
        std::cout << "Found character in range [a-f]" << std::endl;
}
//! [2]


//! [3]
QByteArray x("and");
x.prepend("rock ");         // x == "rock and"
x.append(" roll");          // x == "rock and roll"
x.replace(5, 3, "&");       // x == "rock & roll"
//! [3]


//! [4]
QByteArray ba4("We must be <b>bold</b>, very <b>bold</b>");
qsizetype j = 0;
while ((j = ba4.indexOf("<b>", j)) != -1) {
    std::cout << "Found <b> tag at index position " << j << std::endl;
    ++j;
}
//! [4]


//! [5]
QByteArray().isNull();          // returns true
QByteArray().isEmpty();         // returns true

QByteArray("").isNull();        // returns false
QByteArray("").isEmpty();       // returns true

QByteArray("abc").isNull();     // returns false
QByteArray("abc").isEmpty();    // returns false
//! [5]


//! [6]
QByteArray ba6("Hello");
qsizetype n = ba6.size();    // n == 5
ba6.data()[0];               // returns 'H'
ba6.data()[4];               // returns 'o'
ba6.data()[5];               // returns '\0'
//! [6]


//! [7]
QByteArray().isEmpty();         // returns true
QByteArray("").isEmpty();       // returns true
QByteArray("abc").isEmpty();    // returns false
//! [7]


//! [8]
QByteArray ba8("Hello world");
char *data = ba8.data();
while (*data) {
    std::cout << "[" << *data << "]" << std::endl;
    ++data;
}
//! [8]


//! [9]
QByteArray ba9("Hello, world");
std::cout << ba9[0]; // prints H
ba9[7] = 'W';
// ba9 == "Hello, World"
//! [9]


//! [10]
QByteArray ba10("Stockholm");
ba10.truncate(5);             // ba == "Stock"
//! [10]


//! [11]
QByteArray ba11("STARTTLS\r\n");
ba11.chop(2);                 // ba == "STARTTLS"
//! [11]


//! [12]
QByteArray x12("free");
QByteArray y12("dom");
x12 += y12;
// x == "freedom"
//! [12]


//! [13]
QByteArray().isNull();          // returns true
QByteArray("").isNull();        // returns false
QByteArray("abc").isNull();     // returns false
//! [13]


//! [14]
QByteArray ba14("Istambul");
ba14.fill('o');
// ba == "oooooooo"

ba14.fill('X', 2);
// ba == "XX"
//! [14]


//! [15]
QByteArray x15("ship");
QByteArray y15("air");
x15.prepend(y15);
// x == "airship"
//! [15]


//! [16]
QByteArray x16("free");
QByteArray y16("dom");
x16.append(y16);
// x == "freedom"
//! [16]


//! [17]
QByteArray ba17("Meal");
ba17.insert(1, QByteArrayView("ontr"));
// ba == "Montreal"
//! [17]


//! [18]
QByteArray ba18("Montreal");
ba18.remove(1, 4);
// ba == "Meal"
//! [18]


//! [19]
QByteArray x19("Say yes!");
QByteArray y19("no");
x19.replace(4, 3, y19);
// x == "Say no!"
//! [19]


//! [20]
QByteArray ba20("colour behaviour flavour neighbour");
ba20.replace(QByteArray("ou"), QByteArray("o"));
// ba == "color behavior flavor neighbor"
//! [20]


//! [21]
QByteArray x21("sticky question");
QByteArrayView y21("sti");
x21.indexOf(y21);               // returns 0
x21.indexOf(y21, 1);            // returns 10
x21.indexOf(y21, 10);           // returns 10
x21.indexOf(y21, 11);           // returns -1
//! [21]


//! [22]
QByteArray ba22("ABCBA");
ba22.indexOf("B");            // returns 1
ba22.indexOf("B", 1);         // returns 1
ba22.indexOf("B", 2);         // returns 3
ba22.indexOf("X");            // returns -1
//! [22]


//! [23]
QByteArray x23("crazy azimuths");
QByteArrayView y23("az");
x23.lastIndexOf(y23);           // returns 6
x23.lastIndexOf(y23, 6);        // returns 6
x23.lastIndexOf(y23, 5);        // returns 2
x23.lastIndexOf(y23, 1);        // returns -1
//! [23]


//! [24]
QByteArray ba24("ABCBA");
ba24.lastIndexOf("B");        // returns 3
ba24.lastIndexOf("B", 3);     // returns 3
ba24.lastIndexOf("B", 2);     // returns 1
ba24.lastIndexOf("X");        // returns -1
//! [24]


//! [25]
QByteArray url("ftp://ftp.qt-project.org/");
if (url.startsWith("ftp:"))
{
    // ...
    // Todo
}
//! [25]


//! [26]
QByteArray url26("http://qt-project.org/doc/qt-5.0/qtdoc/index.html");
if (url26.endsWith(".html"))
{
    // ...
    // Todo
}
//! [26]


//! [27]
QByteArray x27("Pineapple");
QByteArray y27 = x27.first(4);
// y == "Pine"
//! [27]


//! [28]
QByteArray x28("Pineapple");
QByteArray y28 = x28.last(5);
// y == "apple"
//! [28]


//! [29]
QByteArray x29("Five pineapples");
QByteArray y29 = x29.sliced(5, 4);     // y == "pine"
QByteArray z29 = x29.sliced(5);        // z == "pineapples"
//! [29]


//! [30]
QByteArray x30("Qt by THE QT COMPANY");
QByteArray y30 = x30.toLower();
// y == "qt by the qt company"
//! [30]


//! [31]
QByteArray x31("Qt by THE QT COMPANY");
QByteArray y31 = x31.toUpper();
// y == "QT BY THE QT COMPANY"
//! [31]


//! [32]
QByteArray ba32("  lots\t of\nwhitespace\r\n ");
ba32 = ba32.simplified();
// ba == "lots of whitespace";
//! [32]


//! [33]
QByteArray ba33("  lots\t of\nwhitespace\r\n ");
ba33 = ba33.trimmed();
// ba == "lots\t of\nwhitespace";
//! [33]


//! [34]
QByteArray x34("apple");
QByteArray y34 = x34.leftJustified(8, '.');   // y == "apple..."
//! [34]


//! [35]
QByteArray x35("apple");
QByteArray y35 = x35.rightJustified(8, '.');    // y == "...apple"
//! [35]


//! [36]
QByteArray str("FF");
bool ok;
int hex = str.toInt(&ok, 16);     // hex == 255, ok == true
int dec = str.toInt(&ok, 10);     // dec == 0, ok == false
//! [36]


//! [37]
QByteArray str37("FF");
bool ok37;
long hex37 = str37.toLong(&ok37, 16);   // hex == 255, ok == true
long dec37 = str37.toLong(&ok37, 10);   // dec == 0, ok == false
//! [37]


//! [38]
QByteArray string38("1234.56");
bool ok38;
double a38 = string38.toDouble(&ok38);   // a == 1234.56, ok == true

string38 = "1234.56 Volt";
a38 = str.toDouble(&ok38);             // a == 0, ok == false
//! [38]

//! [38float]
QByteArray string388("1234.56");
bool ok388;
float a388 = string388.toFloat(&ok388);    // a == 1234.56, ok == true

string388 = "1234.56 Volt";
a388 = str.toFloat(&ok388);              // a == 0, ok == false
//! [38float]

//! [39]
QByteArray text391("Qt is great!");
text391.toBase64();        // returns "UXQgaXMgZ3JlYXQh"

QByteArray text39("<p>Hello?</p>");
text39.toBase64(QByteArray::Base64Encoding | QByteArray::OmitTrailingEquals);      // returns "PHA+SGVsbG8/PC9wPg"
text39.toBase64(QByteArray::Base64Encoding);                                       // returns "PHA+SGVsbG8/PC9wPg=="
text39.toBase64(QByteArray::Base64UrlEncoding);                                    // returns "PHA-SGVsbG8_PC9wPg=="
text39.toBase64(QByteArray::Base64UrlEncoding | QByteArray::OmitTrailingEquals);   // returns "PHA-SGVsbG8_PC9wPg"
//! [39]

//! [40]
QByteArray ba40;
int n40 = 63;
ba40.setNum(n40);           // ba == "63"
ba40.setNum(n40, 16);       // ba == "3f"
//! [40]


//! [41]
int n41 = 63;
QByteArray::number(n41);              // returns "63"
QByteArray::number(n41, 16);          // returns "3f"
QByteArray::number(n41, 16).toUpper();  // returns "3F"
//! [41]


//! [42]
QByteArray ba42 = QByteArray::number(12.3456, 'E', 3);
// ba == 1.235E+01
//! [42]


//! [43]
 static const char mydata[] = {
    '\x00', '\x00', '\x03', '\x84', '\x78', '\x9c', '\x3b', '\x76',
    '\xec', '\x18', '\xc3', '\x31', '\x0a', '\xf1', '\xcc', '\x99',
    /*...*/
    '\x6d', '\x5b'
};

//QByteArray data = QByteArray::fromRawData(mydata, sizeof(mydata));
//QDataStream in(&data, QIODevice::ReadOnly);
//...
//! [43]


//! [44]
QByteArray text394 = QByteArray::fromBase64("UXQgaXMgZ3JlYXQh");
text394.data();            // returns "Qt is great!"

QByteArray::fromBase64("PHA+SGVsbG8/PC9wPg==", QByteArray::Base64Encoding); // returns "<p>Hello?</p>"
QByteArray::fromBase64("PHA-SGVsbG8_PC9wPg==", QByteArray::Base64UrlEncoding); // returns "<p>Hello?</p>"
//! [44]

//! [44ter]
void process(const QByteArray &);

//if (auto result = QByteArray::fromBase64Encoding(encodedData))
    //process(*result);
//! [44ter]

//! [44quater]
//auto result = QByteArray::fromBase64Encoding(encodedData);
//if (result.decodingStatus == QByteArray::Base64DecodingStatus::Ok)
    //process(result.decoded);
//! [44quater]

//! [45]
QByteArray text395 = QByteArray::fromHex("517420697320677265617421");
text395.data();            // returns "Qt is great!"
//! [45]

//! [46]
QString tmp = "test";
QByteArray text396 = tmp.toLocal8Bit();
char *data6 = new char[text396.size()];
strcpy(data6, text396.data());
delete [] data6;
//! [46]

//! [47]
QString tmp7 = "test";
QByteArray text397 = tmp7.toLocal8Bit();
char *data7 = new char[text397.size() + 1];
strcpy(data7, text397.data());
delete [] data7;
//! [47]

//! [48]
QByteArray ba48("ca\0r\0t");
ba48.size();                     // Returns 2.
ba48.constData();                // Returns "ca" with terminating \0.

QByteArray ba481("ca\0r\0t", 3);
ba481.size();                     // Returns 3.
ba481.constData();                // Returns "ca\0" with terminating \0.

QByteArray ba482("ca\0r\0t", 4);
ba482.size();                     // Returns 4.
ba482.constData();                // Returns "ca\0r" with terminating \0.

const char cart[] = {'c', 'a', '\0', 'r', '\0', 't'};
QByteArray ba448(QByteArray::fromRawData(cart, 6));
ba448.size();                     // Returns 6.
ba448.constData();                // Returns "ca\0r\0t" without terminating \0.
//! [48]

//! [49]
QByteArray ba49("ab");
ba49.repeated(4);             // returns "abababab"
//! [49]

//! [50]
QByteArray macAddress = QByteArray::fromHex("123456abcdef");
macAddress.toHex(':'); // returns "12:34:56:ab:cd:ef"
macAddress.toHex(0);   // returns "123456abcdef"
//! [50]

//! [51]
QByteArray text3912 = QByteArray::fromPercentEncoding("Qt%20is%20great%33");
qDebug("%s", text3912.data());      // reports "Qt is great!"
//! [51]

//! [52]
QByteArray text392 = "{a fishy string?}";
QByteArray ba52 = text392.toPercentEncoding("{}", "s");
qDebug("%s", ba52.constData());
// prints "{a fi%73hy %73tring%3F}"
//! [52]

//! [53]
QByteArray ba53 = QByteArrayLiteral("byte array contents");
//! [53]

//! [54]
QByteArray encoded("Qt%20is%20great%33");
QByteArray decoded = encoded.percentDecoded(); // Set to "Qt is great!"
//! [54]

//! [55]
//emscripten::val uint8array = emscripten::val::global("g_uint8array");
//QByteArray byteArray55 = QByteArray::fromEcmaUint8Array(uint8array);
//! [55]

//! [56]
QByteArray byteArray56 = "test";
//emscripten::val uint8array = byteArray.toEcmaUint8Array();
//! [56]

//! [57]
//QByteArray x57 = "Five pineapples"_ba;
//x57.slice(5);     // x == "pineapples"
//x57.slice(4, 3);  // x == "app"
//! [57]

}
