#define BLYNK_TEMPLATE_ID           "TMPL2SW-VQELN"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "tkbt-ZUUlC3vf8bpXViNZonzXK4AG3Xq"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <BlynkSimpleEsp32.h>

char ssid[] = "Microlages-Escritorio";
char pass[] = "4930198001";

// Pinos dos relés
#define rele1 26
#define rele2 27

#define RELAY_ON  LOW
#define RELAY_OFF HIGH

BlynkTimer timer;
WebServer server(80);

// --- Atualiza status no Blynk ---
void atualizarStatus() {
  String status1 = (digitalRead(rele1) == RELAY_ON) ? "Ligado" : "Desligado";
  String status2 = (digitalRead(rele2) == RELAY_ON) ? "Ligado" : "Desligado";

  String mensagem = "Relé 1: " + status1 + " | Relé 2: " + status2;
  Blynk.virtualWrite(V2, mensagem);
}

// --- Controle individual via Blynk ---
BLYNK_WRITE(V0) {
  int value = param.asInt();
  digitalWrite(rele1, value ? RELAY_ON : RELAY_OFF);
  atualizarStatus();
}

BLYNK_WRITE(V1) {
  int value = param.asInt();
  digitalWrite(rele2, value ? RELAY_ON : RELAY_OFF);
  atualizarStatus();
}

// --- Botão "Tudo Off" via Blynk ---
BLYNK_WRITE(V4) {
  int value = param.asInt();

  if (value == 1) {
    Serial.println("Comando: Tudo Off");

    digitalWrite(rele1, RELAY_OFF);
    digitalWrite(rele2, RELAY_OFF);

    atualizarStatus();
    Blynk.virtualWrite(V0, 0);
    Blynk.virtualWrite(V1, 0);

    delay(300);
    Blynk.virtualWrite(V4, 0);
  }
}

// --- Página HTML simples ---
String getHTML() {
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<title>Controle de Relés - Timer Engenharia</title>";
  html += "<style>body{font-family:Arial;text-align:center;background:#f3f3f3;}";
  html += "h2{color:#333;}button{padding:10px 20px;margin:8px;font-size:18px;";
  html += "border:none;border-radius:8px;cursor:pointer;}";
  html += ".on{background:#4CAF50;color:white;} .off{background:#f44336;color:white;}";
  html += "</style></head><body>";
  html += "<h2>💡 Painel de Controle Local</h2>";

  html += "<p><b>Relé 1:</b> " + String(digitalRead(rele1) == RELAY_ON ? "Ligado" : "Desligado") + "</p>";
  html += "<button class='on' onclick=\"fetch('/on1')\">Ligar 1</button>";
  html += "<button class='off' onclick=\"fetch('/off1')\">Desligar 1</button><br>";

  html += "<p><b>Relé 2:</b> " + String(digitalRead(rele2) == RELAY_ON ? "Ligado" : "Desligado") + "</p>";
  html += "<button class='on' onclick=\"fetch('/on2')\">Ligar 2</button>";
  html += "<button class='off' onclick=\"fetch('/off2')\">Desligar 2</button><br>";

  html += "<hr><button class='off' onclick=\"fetch('/alloff')\">🚨 Desligar Tudo</button>";
  html += "<p style='margin-top:20px;color:#777;'>Sistema Integrado ao Blynk Cloud</p>";
  html += "</body></html>";

  return html;
}

// --- Rotas do servidor ---
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

void handleOn1() {
  digitalWrite(rele1, RELAY_ON);
  Blynk.virtualWrite(V0, 1);
  atualizarStatus();
  server.send(200, "text/html", getHTML());
}

void handleOff1() {
  digitalWrite(rele1, RELAY_OFF);
  Blynk.virtualWrite(V0, 0);
  atualizarStatus();
  server.send(200, "text/html", getHTML());
}

void handleOn2() {
  digitalWrite(rele2, RELAY_ON);
  Blynk.virtualWrite(V1, 1);
  atualizarStatus();
  server.send(200, "text/html", getHTML());
}

void handleOff2() {
  digitalWrite(rele2, RELAY_OFF);
  Blynk.virtualWrite(V1, 0);
  atualizarStatus();
  server.send(200, "text/html", getHTML());
}

void handleAllOff() {
  digitalWrite(rele1, RELAY_OFF);
  digitalWrite(rele2, RELAY_OFF);
  Blynk.virtualWrite(V0, 0);
  Blynk.virtualWrite(V1, 0);
  atualizarStatus();
  server.send(200, "text/html", getHTML());
}

// --- Setup ---
void setup() {
  Serial.begin(115200);

  pinMode(rele1, OUTPUT);
  pinMode(rele2, OUTPUT);

  digitalWrite(rele1, RELAY_OFF);
  digitalWrite(rele2, RELAY_OFF);

  WiFi.begin(ssid, pass);
  Serial.print("Conectando ao Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // Inicia o Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  // Configura o servidor local
  server.on("/", handleRoot);
  server.on("/on1", handleOn1);
  server.on("/off1", handleOff1);
  server.on("/on2", handleOn2);
  server.on("/off2", handleOff2);
  server.on("/alloff", handleAllOff);
  server.begin();

  timer.setInterval(2000L, atualizarStatus);

  Serial.println("Sistema iniciado com sucesso!");
}

// --- Loop ---
void loop() {
  Blynk.run();
  timer.run();
  server.handleClient();
}
