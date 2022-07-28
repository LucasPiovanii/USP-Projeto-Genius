/*
      Programa Jogo Genius ("Simons Says")
      Jogo é composto de 4 botões com 4 LEDs coloridos. Jogador deve fazer a mesma sequencia de cores proposta pelo Jogo.

      Componentes:
        - Arduino (Qualquer placa);
        - 4 botões tipo "push-button táctil"
        - 4 LEDs coloridos (vermelho, verde, amarelo e azul)
        - 4 Resistores de 220 Ohms (ou valor adequado para o LED selecionado)
        - 1 Buzzer

      Versão 1.0 - Versão inicial com Jogo de 50 posições e alguns efeitos pré e pós jogo - 14/Jan/2021

 *    * Criado por Cleber Borges - FunBots - @cleber.funbots  *     *

      Instagram: https://www.instagram.com/cleber.funbots/
      Facebook: https://www.facebook.com/cleber.funbots
      YouTube: https://www.youtube.com/channel/UCKs2l5weIqgJQxiLj0A6Atw
      Telegram: https://t.me/cleberfunbots

*/

// Notas para os sons
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

// Melodias:
int melody[] = {
  NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5
};
int melody2[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};
int melody3[] = {
  NOTE_FS5, NOTE_FS5, NOTE_D5, NOTE_B4, NOTE_B4, NOTE_E5,
  NOTE_E5, NOTE_E5, NOTE_GS5, NOTE_GS5, NOTE_A5, NOTE_B5,
  NOTE_A5, NOTE_A5, NOTE_A5, NOTE_E5, NOTE_D5, NOTE_FS5,
  NOTE_FS5, NOTE_FS5, NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5
};
int durations3[] = {
  8, 8, 8, 4, 4, 4,
  4, 5, 8, 8, 8, 8,
  8, 8, 8, 4, 4, 4,
  4, 5, 8, 8, 8, 8
};
int songLength = sizeof(melody3)/sizeof(melody3[0]);
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
int melody4[] = {NOTE_A4, NOTE_A4, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, NOTE_E5, NOTE_F5, NOTE_C5, NOTE_A4, NOTE_F4, NOTE_C5, NOTE_A4};
int durations4[]  = {4, 4, 4, 5, 16, 4, 5, 16, 2, 4, 4, 4, 5, 16, 4, 5, 16, 2};
int tuneSize = sizeof(melody4) / sizeof(int);

// Definição de Pinos
#define pino_BotaoVM  3
#define pino_BotaoAM  7
#define pino_BotaoVD  9
#define pino_BotaoAZ  5
#define pino_LedVM    2
#define pino_LedAM    6
#define pino_LedVD    8
#define pino_LedAZ    4
#define pino_Buzzer   11

// Constantes
const int tamMemoria = 50;      // Número máximo de combinações ou fases de jogo
const int tempoCor = 1000;      // tempo de cada cor, 1000 millisegundos

// Variáveis de programa
int statusBotaoVM = 0;      // Status dos botões
int statusBotaoAM = 0;
int statusBotaoVD = 0;
int statusBotaoAZ = 0;

int currentTime = 0;        // temporizadores
int lastTime = 0;

int demoLed = 0;          // Indicador de modo demonstração pré-jogo

int statusJogo = 0;       // 0 = modo demonstração ; 1 = modo Jogo
int memJogo[tamMemoria];  // array com sequencia de cores para jogar responder
int etapaJogo;            // 0 = introdução; 1 = jogo; 2 = perdeu; 3 = ganhou
int faseJogo = 1;         // evolução do jogador, vai até o valor de tamMemoria
int respJogador = 0;       // guarda resposta do jogador
int botaoPress = 0;       // variável para guardar botão pressionado pelo jogador
int perdeuJogo = 0;       // indicador para perdeu o jogo
int tempoJogador = 5000;  // Tempo da vez do jogador, para cada cor

/*
   SETUP
*/
void setup() {
  // Serial para debug
  Serial.begin(9600);

  // Configuração dos pinos
  pinMode(pino_BotaoVM, INPUT_PULLUP);
  pinMode(pino_BotaoAM, INPUT_PULLUP);
  pinMode(pino_BotaoVD, INPUT_PULLUP);
  pinMode(pino_BotaoAZ, INPUT_PULLUP);
  pinMode(pino_LedVM, OUTPUT);
  pinMode(pino_LedAM, OUTPUT);
  pinMode(pino_LedVD, OUTPUT);
  pinMode(pino_LedAZ, OUTPUT);
  pinMode(pino_Buzzer, OUTPUT);

  // Registro de tempo e inicializa randomização
  lastTime = millis();
  randomSeed(analogRead(0));
}

/*
   LOOP
*/
void loop() {
  // Loop fica em dois whiles, ou está no modo pré-jogo (demonstração), ou está no modo jogo
  while (statusJogo != 1) {
    modoDemo();
    leituraBotoes();  // Se pressionar algum botão, sai do modo demo e entra no modo jogo
    Serial.print(".");
  }
  while (statusJogo == 1) {
    modoJogo();
  }
}


/*
***** FUNÇÕES ******
*/
// Função do modo demonstração ou pré-jogo, consiste num efeito dos leds apenas
void modoDemo() {
  currentTime = millis();
  if ((currentTime - lastTime) > 100) {
    demoLed++;
    if (demoLed > 9) {
      demoLed = 1;
    }
    lastTime = currentTime;
  }
  switch (demoLed) {
    case 1:
      apagaLeds();
      digitalWrite(pino_LedVM, HIGH);
      break;
    case 2:
      digitalWrite(pino_LedAM, HIGH);
      break;
    case 3:
      digitalWrite(pino_LedVD, HIGH);
      break;
    case 4:
      digitalWrite(pino_LedAZ, HIGH);
      break;
    case 5:
      digitalWrite(pino_LedVM, LOW);
      break;
    case 6:
      digitalWrite(pino_LedAM, LOW);
      break;
    case 7:
      digitalWrite(pino_LedVD, LOW);
      break;
    case 8:
      digitalWrite(pino_LedAZ, LOW);
      break;
    case 9:
      apagaLeds();
      break;
    default:
      apagaLeds();
      break;
  }
  delay (100);
}

// Função Modo Jogo, dividida em duas partes, inicialização e Jogo propriamente dito
void modoJogo() {
  switch (etapaJogo) {
    case 0:
      inicioJogo();   // Faz efeito de leds de inicialização
      etapaJogo++;
      break;
    case 1:
      turnoArduino();
      turnoJogador();
      break;
  }
  delay (100);
}

// Função de efeitos de início do jogo e carregamento da memória
void inicioJogo() {
  Serial.println("Iniciando Jogo...");
  somInicio();
  for (int i = 0; i < 10; i++) {
    digitalWrite(pino_LedVM, LOW);
    delay(40);

    digitalWrite(pino_LedAM, HIGH);
    delay(40);
    //somInicio();
    digitalWrite(pino_LedVD, LOW);
    delay(40);
    //somInicio();
    digitalWrite(pino_LedAZ, HIGH);
    delay(40);
    // somInicio();
    digitalWrite(pino_LedVM, HIGH);
    delay(40);
    // somInicio();
    digitalWrite(pino_LedAM, LOW);
    delay(40);
    //  somInicio();
    digitalWrite(pino_LedVD, HIGH);
    delay(40);
    // somInicio();
    digitalWrite(pino_LedAZ, LOW);
    delay(40);
  }
  digitalWrite(pino_LedAM, HIGH);
  digitalWrite(pino_LedAZ, HIGH);
  delay(1000);

  // sorteia memoria
  for (int i = 0; i < tamMemoria ; i++) {
    memJogo[i] = random(1, 5);              // randomiza cores: 1 = Verm; 2 = Amar; 3 = Verd; 4 = Azul
  }

  // Zera variáveis
  apagaLeds();
  respJogador = 0;
  perdeuJogo = 0;
  faseJogo = 1;
}

// Função de Jogo para turno do Arduino, acender os Leds conforme memória e fase atual
void turnoArduino() {
  Serial.print("Turno Arduino, Fase: ");
  Serial.println(faseJogo);       // variável faseJogo é o quanto o Jogador vai avançando, Arduino exibe até onde Jogador está

  for (int i = 0; i < faseJogo ; i++) {
    switch (memJogo[i]) {
      case 1:
        acendeLeds(1, 0, 0, 0);
        break;
      case 2:
        acendeLeds(0, 1, 0, 0);
        break;
      case 3:
        acendeLeds(0, 0, 1, 0);
        break;
      case 4:
        acendeLeds(0, 0, 0, 1);
        break;
      default:
        acendeLeds(0, 0, 0, 0);
        break;
    }
    delay(tempoCor);
    apagaLeds();
    delay(100);
  }
}

// Função de Jogo para o turno do Jogador,
void turnoJogador() {
  Serial.print("Turno Jogador, Fase: ");
  Serial.println(faseJogo);
  int terminoTurno = 0;

  // Para cada fase alcançada, jogador tem que repetir sequencia do Arduino
  for (int i = 0 ; i < faseJogo ; i++) {
    botaoPress = leituraBotoesJogo(i);    // Checa botão pressionado pelo jogador
    if (botaoPress == 1) {    // Pressionou corretamente
      Serial.println("Resposta certa");
      terminoTurno = 1;
      delay (100);
    } else {                  // Errou
      Serial.println("Resposta errada, Perdeu o jogo!");
      perdeuJogo == 1;
      statusJogo = 0;
      etapaJogo = 0;
      perdeJogo();
      break;
    }
  }
  delay(500);
  faseJogo++;             // Incrementa fase
  if (faseJogo == memJogo) {
    ganhouJogo();     // ganhou jogo e faz efeito do ganhador
  }
}

// Função para ler botões no modo demonstação, com lógica para sair do modo se pressionou botão
void leituraBotoes() {
  statusBotaoVM = !digitalRead(pino_BotaoVM);
  statusBotaoAM = !digitalRead(pino_BotaoAM);
  statusBotaoVD = !digitalRead(pino_BotaoVD);
  statusBotaoAZ = !digitalRead(pino_BotaoAZ);
  if (statusJogo == 0) {
    if (statusBotaoVM || statusBotaoAM || statusBotaoVD || statusBotaoAZ) { // algum botão foi pressionado
      apagaLeds();
      demoLed = 1;
      statusJogo = 1;
    }
  }
  delay(50);
}

// Função para leitura dos botões durante jogo, inclui debounce para evitar leituras espúrias
int leituraBotoesJogo(int fase) {
  int botao = 0;
  int debounce = 0;
  int tempoTurno = 0;
  int inicioTurno = millis();
  while (botao == 0 || debounce == 0) {   // fica dentro do while enquanto não pressionar botão e debounce acabar
    statusBotaoVM = !digitalRead(pino_BotaoVM);
    statusBotaoAM = !digitalRead(pino_BotaoAM);
    statusBotaoVD = !digitalRead(pino_BotaoVD);
    statusBotaoAZ = !digitalRead(pino_BotaoAZ);
    if (statusBotaoVM) botao = 1;
    if (statusBotaoAM) botao = 2;
    if (statusBotaoVD) botao = 3;
    if (statusBotaoAZ) botao = 4;
    acendeLeds(statusBotaoVM, statusBotaoAM, statusBotaoVD, statusBotaoAZ);
    // Faz debounce, só sai do while se botão foi depressionado
    if (statusBotaoVM == 0 && statusBotaoAM  == 0 && statusBotaoAM  == 0 && statusBotaoAM  == 0 && botao > 0 ) {
      debounce = 1;
    }
    delay(100);
    tempoTurno = millis();
    if ((tempoTurno - inicioTurno) > tempoJogador) return 0;  // Tempo de 5 segundos excedido
  }
  // confere se botão pressionado foi o correto e retorna com resultado
  if (botao == memJogo[fase]) {
    return 1;     // Acertou
  } else {
    return 0;     // Errou
  }
}

// Função com efeitos de Perdeu o Jogo
void perdeJogo() {
  somPerdeu();
  for (int i = 0; i < 15; i++) {
    digitalWrite(pino_LedVM, LOW);
    digitalWrite(pino_LedAM, LOW);
    digitalWrite(pino_LedVD, LOW);
    digitalWrite(pino_LedAZ, LOW);
    delay(100);
    digitalWrite(pino_LedVM, HIGH);
    digitalWrite(pino_LedAM, HIGH);
    digitalWrite(pino_LedVD, HIGH);
    digitalWrite(pino_LedAZ, HIGH);
    delay(100);
  }
}

// Função com efeitos de Ganhou o Jogo
void ganhouJogo() {
  somGanhou();
  for (int i = 0; i < 20; i++) {
    digitalWrite(pino_LedVM, LOW);
    delay(40);
    digitalWrite(pino_LedAM, HIGH);
    delay(40);
    digitalWrite(pino_LedVD, LOW);
    delay(40);
    digitalWrite(pino_LedAZ, HIGH);
    delay(40);
    digitalWrite(pino_LedVM, HIGH);
    delay(40);
    digitalWrite(pino_LedAM, LOW);
    delay(40);
    digitalWrite(pino_LedVD, HIGH);
    delay(40);
    digitalWrite(pino_LedAZ, LOW);
    delay(40);
  }
}

// Função para acender os Leds, conforme status passado pelas variáveis
void acendeLeds(int ledVM, int ledAM, int ledVD, int ledAZ) {
  digitalWrite(pino_LedVM, ledVM);
  digitalWrite(pino_LedAM, ledAM);
  digitalWrite(pino_LedVD, ledVD);
  digitalWrite(pino_LedAZ, ledAZ);
  if (ledVM) somVM();
  if (ledAM) somAM();
  if (ledVD) somVD();
  if (ledAZ) somAZ();
}

// Função para apagar todos os Leds
void apagaLeds() {
  digitalWrite(pino_LedVM, LOW);
  digitalWrite(pino_LedAM, LOW);
  digitalWrite(pino_LedVD, LOW);
  digitalWrite(pino_LedAZ, LOW);
}

// Funções de Sons
void somVM() {
  tone(pino_Buzzer, melody[0], 100);
}

void somAM() {
  tone(pino_Buzzer, melody[1], 100);
}

void somVD() {
  tone(pino_Buzzer, melody[2], 100);
}

void somAZ() {
  tone(pino_Buzzer, melody[3], 100);
}

void somInicio() {
  for (int thisNote = 0; thisNote < songLength; thisNote++) {
    int duration = 1000 / durations3[thisNote];
    tone(pino_Buzzer, melody3[thisNote], duration);
    int pause = duration * 1.3;
    delay(pause);
    noTone(pino_Buzzer);
  }
}

void somPerdeu() {
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(pino_Buzzer, melody2[thisNote], noteDuration);
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    noTone(pino_Buzzer);
  }
}

void somGanhou() {
  for (int thisNote = 0; thisNote < tuneSize; thisNote++) {
    int noteDuration = (int)((1000 * (60 * 4 / 120)) / durations4[thisNote] + 0.);
    tone(pino_Buzzer, melody4[thisNote],noteDuration);
    int pauseBetweenNotes = noteDuration * 1.20;
    delay(pauseBetweenNotes);
    noTone(pino_Buzzer);
  }
}
