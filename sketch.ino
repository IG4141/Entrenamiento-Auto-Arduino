// --- Red neuronal Arduino ---
// Arquitectura: 2 entradas, 3 ocultas, 4 salidas
// Basado en el proyecto "Coche Arduino con Inteligencia Artificial"

float tanh_activation(float x) {
  return tanh(x);
}

//  Pesos entrenados (ejemplo; reemplaza con los tuyos)
float W1[3][3] = {
  {0.5, -0.12, 0.88},
  {-0.31, 0.74, 0.22},
  {0.15, 0.33, -0.41} // bias
};

float W2[4][4] = {
  {0.62, -0.33, 0.22, 0.41},
  {-0.55, 0.91, -0.28, 0.35},
  {0.18, -0.42, 0.66, -0.31},
  {0.27, 0.51, -0.17, 0.73} // bias
};

void forward(float x1, float x2, float output[4]) {
  float hidden[3];

  // Capa oculta
  for (int i = 0; i < 3; i++) {
    hidden[i] = tanh_activation(
      x1 * W1[0][i] +
      x2 * W1[1][i] +
      1.0 * W1[2][i] // bias
    );
  }

  // Capa de salida
  for (int j = 0; j < 4; j++) {
    float sum = 1.0 * W2[0][j]; // bias
    for (int i = 0; i < 3; i++) {
      sum += hidden[i] * W2[i + 1][j];
    }
    output[j] = tanh_activation(sum);
  }
}

void setup() {
  Serial.begin(9600);
  float salida[4];

  Serial.println("=== Simulación de red neuronal ===");

  //  Entradas de prueba
  float entradas[3][2] = {
    {-1, -1},
    {0, 1},
    {1, -1}
  };

  for (int t = 0; t < 3; t++) {
    float x1 = entradas[t][0];
    float x2 = entradas[t][1];
    forward(x1, x2, salida);

    Serial.print("Entrada: (");
    Serial.print(x1);
    Serial.print(", ");
    Serial.print(x2);
    Serial.println(")");

    for (int i = 0; i < 4; i++) {
      Serial.print("  Salida ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(salida[i]);
    }
    Serial.println("-------------------");
  }
}

void loop() {
  // Aquí podrías leer sensores o ejecutar la red en bucle
}
