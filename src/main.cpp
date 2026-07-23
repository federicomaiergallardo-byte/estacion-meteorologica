#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// Definir el pin del DHT11 (GPIO 34 es de entrada exclusiva, perfecto para este sensor)
#define DHTPIN 13     
#define DHTTYPE DHT11   

DHT dht(DHTPIN, DHTTYPE);

// Configuración de la pantalla LCD (Dirección 0x27, 16 columnas, 2 filas)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  
  // Inicializar bus I2C asegurando los pines SDA (21) y SCL (22)
  Wire.begin(21, 22);
  lcd.init();
  lcd.backlight();
  
  // Inicializar el sensor DHT
  dht.begin();
  
  // Mensaje de bienvenida en la pantalla
  lcd.setCursor(0, 0);
  lcd.print("Estacion Meteo");
  lcd.setCursor(0, 1);
  lcd.print("Iniciando...");
  delay(2000);
  lcd.clear();
}

void loop() {
  // El DHT11 necesita al menos 2 segundos entre lecturas
  delay(2000);

  // Leer humedad
  float h = dht.readHumidity();
  // Leer temperatura en Celsius
  float t = dht.readTemperature();

  // Verificar si hubo un error de lectura
  if (isnan(h) || isnan(t)) {
    Serial.println("Falla al leer el sensor DHT11!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Error Sensor!");
    return;
  }

  // Imprimir por el Monitor Serie para control
  Serial.print("Humedad: ");
  Serial.print(h);
  Serial.print("%  ");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("°C");

  // Mostrar datos limpios en la Pantalla LCD
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print((char)223); // Símbolo de grado (°)
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Humedad: ");
  lcd.print(h);
  lcd.print("%");
}