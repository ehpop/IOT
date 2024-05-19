#define LOW 0
#define HIGH 1

#define OUTPUT 1

int licznik = 0;
int liczba = 0;
int minimum, maksimum, jasnosc, wilgotnosc, temperatura;

void Znak(int iNumer)
{
    digitalWrite(8, ((iNumer == 0) || (iNumer == 1) || (iNumer == 7)) ? HIGH : LOW);
    switch (iNumer)
    {
    case 0:
        PORTD = 0b00000000;
        break;
    case 1:
        PORTD = 0b11100100;
        break;
    case 2:
        PORTD = 0b10010010;
        break;
    case 3:
        PORTD = 0b11000010;
        break;
    case 4:
        PORTD = 0b01100110;
        break;
    case 5:
        PORTD = 0b01001010;
        break;
    case 6:
        PORTD = 0b00001010;
        break;
    case 7:
        PORTD = 0b11100000;
        break;
    case 8:
        PORTD = 0b00000010;
        break;
    case 9:
        PORTD = 0b01000010;
        break;
    default:
        PORTD = 0b11011000;
    }
}

void setup()
{
    for (int i = 2; i < 9; i++)
    {
        pinMode(i, OUTPUT);
    }
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    delay(1000);
    minimum = analogRead(0);
    maksimum = minimum;
}

void loop()
{
    digitalWrite(11, LOW);
    Znak(liczba % 10);

    digitalWrite(10, HIGH);
    delay(2);
    digitalWrite(10, LOW);
    Znak((liczba / 10) % 10);

    digitalWrite(11, HIGH);
    delay(2);

    if (licznik++ > 100)
    {
        jasnosc = analogRead(0);
        if (minimum > jasnosc)
        {
            minimum = jasnosc;
        }
        if (maksimum < jasnosc)
        {
            maksimum = jasnosc;
        }
        if (minimum != maksimum)
        {
            jasnosc = 99 * (jasnosc - minimum) / (maksimum - minimum);
        }
        liczba = jasnosc;
        licznik = 0;
    }
}
