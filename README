# cpp-vector

My own implementation of std::vector from c++ STL library. Made for University's OOP course

<h2>Eksperimentuotų funkcijų pavyzdžiai</h2>

<h3>#1 push_back()</h3>

Code:

    Vector<std::string> letters;
 
    letters.push_back("abc");
    std::string s{"def"};
    letters.push_back(std::move(s));
 
    std::cout << "std::vector "letters" holds: ";
    for (auto&& e : letters) std::cout << std::quoted(e) << ' ';
 
    std::cout << "\nMoved-from string "s" holds: " << std::quoted(s) << '\n';}


Possible output:

`std::vector "letters" holds: "abc" "def" 
Moved-from string "s" holds: "" `

My output:

`std::vector "letters" holds: "abc" "def" 
Moved-from string "s" holds: ""`

<h3>#2 pop_back()</h3>

Code:

    Vector<int> numbers;
 
    print(numbers); 
 
    numbers.push_back(5);
    numbers.push_back(3);
    numbers.push_back(4);
 
    print(numbers); 
 
    numbers.pop_back();
 
    print(numbers); 

Expected output:

`[ ]
[ 5 3 4 ]
[ 5 3 ]`

My output:

`[ ]
[ 5 3 4 ]
[ 5 3 ]`

<h3>#3 size()</h3>

Code:

    Vector<int> nums {1, 3, 5, 7};
 
    std::cout << "nums contains " << nums.size() << " elements.\n";

Expected output:

` nums contains 4 elements.`

My output:

`nums contains 4 elements.`

<h3>#4 front()</h3>

Code:

     Vector<char> letters {'a', 'b', 'c', 'd', 'e', 'f'};
 
    if (!letters.empty())
        std::cout << "The first character is '" << letters.front() << "'.\n";

Expected output:

` The first character is 'a'.`

My output:

`The first character is 'a'.`

<h3>#5 back()</h3>

Code:

    Vector<char> letters {'a', 'b', 'c', 'd', 'e', 'f'};
 
    if (!letters.empty())
        std::cout << "The last character is '" << letters.back() << "'.\n";

Expected output:

` The last character is 'f'.`

My output:

`The last character is 'f'.`

<h2>Tuščio konteinerio užpildymo laikai:</h2>

| Įrašų kiekis  | 1tūkst.| 10tūkst.| 100tūkst.| 1mil.| 10mil. | 100mil.|
| ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |------------- |
| std::vector| 0.00019606 s| 0.00108902 s  | 0.00928451 s | 0.0343596 s | 0.264555 s | 1.84569 s |
| Mano implementuotas vektorius| 0.000116918 s | 0.000832601 s | 0.00726801 s | 0.0208363 s | 0.166015 s | 1.52554 s |

* Buvo pildyta integer tipo kintamaisiais

* Mano implementuoto vektoriaus sparta truputį greitesnė


<h2> std::vector ir mano vektoriaus persiskirstymai (100mil. įrašų) </h2>

std::vector - 28 perskirstymai

Mano vektorius - 9 perskirstymai

**Išvada:**

* Savo implementacijoje specialiai buvo padaryta, kad didinamas kiekis būtų 10x kiekvieną kart

<h2>std::vector ir mano vektoriaus palyginimas V2.0 programos versijoje </h2>

<br>

**std::vector**

| Įrašų kiekis  | 1mil.|
| ------------- | ------------- |
| Failo nuskaitymo trukmė| 0.28493 s|
| Nuskaityto failo duomenų pertvarkymas(studentų sudėjimas į vektorių)| 8.50817 s |
| Studentų rūšiavimas pagal galutinį balą(sort)  | 3.50756 s  |
| Studentų dalijimas į 2-i grupes | 1.07922 s  |
| Padalintų studentų išvedimas į 2-u naujus failus | 0.867342 s  |
| Visos programos vykdymo laikas | 14.5268 s  |

**Mano implementuotas vektorius**

| Įrašų kiekis  | 1mil.|
| ------------- | ------------- |
| Failo nuskaitymo trukmė| 0.286195 s|
| Nuskaityto failo duomenų pertvarkymas(studentų sudėjimas į vektorių)| 5.27224 s |
| Studentų rūšiavimas pagal galutinį balą(sort)  | 3.29154 s |
| Studentų dalijimas į 2-i grupes | 0.44313 s  |
| Padalintų studentų išvedimas į 2-u naujus failus | 0.669543 s  |
| Visos programos vykdymo laikas | 10.2137 s  |

**Išvados:**

* Mano implementuotas vektorius specifinėje operacijoje yra žymiai greitesnis

* Su didesniu duomenų kiekiu skirtumas tik didėtų