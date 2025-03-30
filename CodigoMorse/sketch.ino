#define UNIDADE_TEMPO 100 // Unidade de medida (em milisegundos) do sinal.
#define SOM 400           // Barulho do sinal (frequência em Hertz)

unsigned int pino = 2; // Pino de output do arduino


String mensagem;            // Mensagem a ser codificada
String mensagem_morse = ""; // Mensagem codificada

char letras[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
String caracteres_morse[27] = {".-", "-...", "-.-.", 
"-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", 
".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", 
"-", "..-", "...-", ".--", "-..-", "-.--", "--.."};

void codificar(String mensagem, String *mensagem_morse);
void piscar_mensagem(String mensagem_morse, int pino);
void piscar_ponto(int pino);
void piscar_traco(int pino);
void intervalo_letra(int pino);
void intervalo_palavra(int pino);
void intervalo_frase(int pino);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);

  pinMode(pino, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0)
  {
    mensagem = Serial.readString();
    codificar(mensagem, &mensagem_morse);

    piscar_mensagem(mensagem_morse, pino);

  }
}

void piscar_mensagem(String mensagem_morse, int pino)
{
  int i;
  char caracter;

  for (i = 0; i < mensagem_morse.length(); i++)
  {
    caracter = mensagem_morse[i];

    switch (caracter)
    {
      case '.':
        piscar_ponto(pino);
        break;
      case '-':
        piscar_traco(pino);
        break;
      case '_':
        intervalo_letra(pino);
        break;
      case ' ':
        intervalo_palavra(pino);
        break;
      case '|':
        intervalo_frase(pino);
        break;
    }
  }
}

void intervalo_frase(int pino)
{
  digitalWrite(pino, LOW);
  noTone(pino);
  delay(10 * UNIDADE_TEMPO);
}

void intervalo_palavra(int pino)
{
  digitalWrite(pino, LOW);
  noTone(pino);
  delay(7 * UNIDADE_TEMPO);
}

void intervalo_letra(int pino)
{
  digitalWrite(pino, LOW);
  noTone(pino);
  delay(2 * UNIDADE_TEMPO);
}

void piscar_ponto(int pino)
{
  digitalWrite(pino, HIGH);
  tone(pino, SOM);
  delay(UNIDADE_TEMPO);
  noTone(pino);
  digitalWrite(pino, LOW);
  delay(UNIDADE_TEMPO);
}

void piscar_traco(int pino)
{
  digitalWrite(pino, HIGH);
  tone(pino, SOM);
  delay(3 * UNIDADE_TEMPO);
  noTone(pino);
  digitalWrite(pino, LOW);
  delay(UNIDADE_TEMPO);
}

void codificar(String mensagem, String *mensagem_morse)
{
  int i, j, caracter_num;

  mensagem.toLowerCase();

  // Percorre a palavra a ser codificada
  for (i = 0; i < mensagem.length() - 1; i++)
  {
    caracter_num = (int) mensagem[i] - 97;

    if (caracter_num == -65)
      *mensagem_morse += " ";
    else if (caracter_num == -158)
      *mensagem_morse += "|";
    else 
    {
      *mensagem_morse += caracteres_morse[caracter_num];
      *mensagem_morse += "_";
    }
  }

}
