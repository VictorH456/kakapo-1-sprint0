// Constantes
const int ntcPin = A0; // Pino conectado ao divisor de tensão
const float seriesResistor = 5000.0; // Resistor fixo (em ohms)
const float nominalResistance = 5000.0; // Resistência nominal do NTC a 25°C
const float nominalTemperature = 25.0; // Temperatura nominal em graus Celsius
const float bCoefficient = 3950.0; // Coeficiente Beta do NTC
const float supplyVoltage = 5.0; // Tensão de alimentação (em volts)

void setup() {
  Serial.begin(9600); // Inicializa a comunicação serial
}

void loop() {
  // Lê a tensão no pino analógico
  int analogValue = analogRead(ntcPin);
  float voltage = analogValue * (supplyVoltage / 1023.0);

  // Calcula a resistência do NTC
  float ntcResistance = seriesResistor * (supplyVoltage / voltage - 1);

  // Fórmula para temperatura (em Kelvin)
  float temperatureKelvin = 1.0 / (1.0 / (nominalTemperature + 273.15) + 
                        (1.0 / bCoefficient) * log(ntcResistance / nominalResistance));

  // Converte para Celsius
  float temperatureCelsius = temperatureKelvin - 273.15+3;

  // Exibe o valor no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(temperatureCelsius);
  Serial.println(" °C");

  delay(1000); // Atualiza a leitura a cada 1 segundo
}
