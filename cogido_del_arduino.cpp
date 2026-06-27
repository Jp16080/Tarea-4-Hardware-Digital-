// --- PINES DE ENTRADA ---
const int pinA0 = 2;
const int pinA1 = 3;
const int pinB0 = 4;
const int pinB1 = 5;
const int pinS0 = 6;
const int pinS1 = 7;

// --- PINES DE SALIDA  ---
// Ahora la lógica del software se adapta a tu conexión física
const int ledR0 = 10;    // LED Derecho (Bit 0)
const int ledR1 = 9;     // LED Central (Bit 1)
const int ledCarry = 8;  // LED Izquierdo (Acarreo)

void setup() {
  // CORRECCIÓN 1: Cambiado de INPUT_PULLUP a INPUT normal.
  // Como ya tienes resistencias físicas hacia tierra (Pull-down) en Tinkercad, 
  // no necesitas la resistencia interna del Arduino.
  pinMode(pinA0, INPUT);
  pinMode(pinA1, INPUT);
  pinMode(pinB0, INPUT);
  pinMode(pinB1, INPUT);
  pinMode(pinS0, INPUT);
  pinMode(pinS1, INPUT);

  pinMode(ledR0, OUTPUT);
  pinMode(ledR1, OUTPUT);
  pinMode(ledCarry, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // CORRECCIÓN 2: Eliminado el "!" (NOT).
  // Al usar resistencias Pull-down, encender el switch manda un 1 (HIGH).
  // No necesitamos invertir la lectura.
  int a0 = digitalRead(pinA0);
  int a1 = digitalRead(pinA1);
  int b0 = digitalRead(pinB0);
  int b1 = digitalRead(pinB1);
  int s0 = digitalRead(pinS0);
  int s1 = digitalRead(pinS1);

  int A = (a1 << 1) | a0;
  int B = (b1 << 1) | b0;

  int seleccion = (s1 << 1) | s0;

  int resultado = 0;
  int carry = 0;
  String nombreOp = "";

  switch (seleccion) {
    case 0:
      resultado = A & B;
      nombreOp = "AND";
      break;
    case 1:
      resultado = A | B;
      nombreOp = "OR";
      break;
    case 2:
      resultado = A ^ B;
      nombreOp = "XOR";
      break;
    case 3:
      resultado = (A + B) & 0b11;
      carry = (A + B) >> 2;
      nombreOp = "SUMA";
      break;
  }

  int r0 = resultado & 0b01;
  int r1 = (resultado >> 1) & 0b01;

  digitalWrite(ledR0, r0);
  digitalWrite(ledR1, r1);
  digitalWrite(ledCarry, carry);

  // El monitor serie estaba perfecto, te servirá mucho para ver qué está leyendo el Arduino
  Serial.print("A=");
  Serial.print(A);
  Serial.print(" B=");
  Serial.print(B);
  Serial.print(" Operacion=");
  Serial.print(nombreOp);
  Serial.print(" Resultado=");
  Serial.print(resultado);
  Serial.print(" Carry=");
  Serial.println(carry);

  delay(200);
}
