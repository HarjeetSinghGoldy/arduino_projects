
int xValue = 0; // wartość odczytu osi X
int yValue = 0; // wartość odczytu osi Y
int bValue = 0; // wartość odczytu przycisku
 
void setup()
{
  Serial.begin(9600); // Otwieramy port szeregowy
  pinMode(2, INPUT);  // Konfigurujemy Pin 2 jako wejście
}
 
void loop()
{
  // Odczytujemy wartości portu analogowego A0 i A1
  xValue = analogRead(A0);        
  yValue = analogRead(A1);  
 
  // Odczytujemy wartość stanu logicznego na pinie 2
  bValue = digitalRead(2);  
 
  // Wyświetlamy nasze dane, oddzielając je przecinkiem                     
  Serial.print(xValue);
  Serial.print(",");
  Serial.print(yValue);
  Serial.print(",");
  Serial.print(!bValue);
 
  // Kończymy znakiem nowej linii ułatwiającym późniejszą analizę
   Serial.print(".");
 
  // Małe opóźnienie przed następnym pomiarem
  delay(2);                     
}
