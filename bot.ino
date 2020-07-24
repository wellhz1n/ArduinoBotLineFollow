
#pragma region Sensores
//Estamos Utilizando Apenas estes sensores
const int SensorL1 = 5;
const int SensorR1 = 7;
const int SensorL2 = 4;

const int SensorR2 = 2;
#pragma endregion
//Motor Direito;
const int INI1 = 8; //Sentido Horario
const int INI2 = 9; //Sentido AntiHorario

const int INI3 = 10;
const int INI4 = 11;
//Pinos que regulam a velocidade;
const int PinVelocidadeR = 6;
const int PinVelocidadeL = 3;
//Velocidade min:0 max 255
const int Velocidade = 150;

//Metodo que controla a Velocidade
void SpeedControl(char Lado = 'A', int valor = 255, bool Aumentar = true)
{
    int _vel = Velocidade;
    if (_vel + valor <= 255 || _vel - valor >= 0)
    {
        switch (Lado)
        {
        case 'A':
            analogWrite(PinVelocidadeL, Aumentar ? _vel += valor : _vel -= valor);
            analogWrite(PinVelocidadeR, Aumentar ? _vel += valor : _vel -= valor);
            break;
        case 'L':
            analogWrite(PinVelocidadeL, Aumentar ? _vel += valor : _vel -= valor);
            break;
        case 'R':
            analogWrite(PinVelocidadeR, Aumentar ? _vel += valor : _vel -= valor);
            break;
        default:
            break;
        }
    }
    else
    {
        switch (Lado)
        {
        case 'A':
            analogWrite(PinVelocidadeL, Velocidade);
            analogWrite(PinVelocidadeR, Velocidade);
            break;
        case 'L':
            analogWrite(PinVelocidadeL, Velocidade);
            break;
        case 'R':
            analogWrite(PinVelocidadeR, Velocidade);
            break;
        default:
            break;
        }
    }
}
//Só faz o led Piscar obs: é só frufru
void Piscar()
{
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
    delay(200);
    digitalWrite(12, HIGH);
    delay(1000);
    digitalWrite(12, LOW);
}
//Obvio
void Parar()
{
    digitalWrite(INI1, LOW);
    digitalWrite(INI3, LOW);
    digitalWrite(INI2, LOW);
    digitalWrite(INI4, LOW);
}
//Obvio
void Frente()
{
    Parar();
    SpeedControl();
    digitalWrite(INI1, HIGH);
    digitalWrite(INI3, HIGH);
}

void setup()
{
    pinMode(12, OUTPUT);
    pinMode(SensorL1, INPUT);
    pinMode(SensorL2, INPUT);
    pinMode(SensorR1, INPUT);
    pinMode(SensorR2, INPUT);

    pinMode(INI1, OUTPUT);
    pinMode(INI2, OUTPUT);
    pinMode(INI3, OUTPUT);
    pinMode(INI4, OUTPUT);
    pinMode(PinVelocidadeR, OUTPUT);
    pinMode(PinVelocidadeL, OUTPUT);
    SpeedControl();
    Piscar();
}

void loop()
{
    digitalWrite(12, LOW);
    //Quando o SpeedControl está vazio ele aplica a velociade padrão para ambos os motores :P
    SpeedControl();
    //Verifica deve ir Para Frente
    if (digitalRead(SensorL1) == 1 && digitalRead(SensorR1) == 0 && digitalRead(SensorL2) == 0)
    {
        Parar();
        Frente();
    }
     //Vira para Direita
    if (digitalRead(SensorL1) == 1 && digitalRead(SensorR1) == 1)
    {
        Parar();
        digitalWrite(INI2, HIGH);
        digitalWrite(INI3, HIGH);
    }
    //Vira para Esquerda
    if (digitalRead(SensorL1) == 1 && digitalRead(SensorL2) == 1)
    {
        Parar();
        digitalWrite(INI1, HIGH);
        digitalWrite(INI4, HIGH);
    }
    //Para caso sai da Fita
    if (digitalRead(SensorL1) == 0 && digitalRead(SensorR1) == 0 && digitalRead(SensorL2) == 0)
    {
        Parar();
        digitalWrite(12, HIGH);
    }
}
