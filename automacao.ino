#define BLYNK_TEMPLATE_ID           "TMPL2SW-VQELN"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "tkbt-ZUUlC3vf8bpXViNZonzXK4AG3Xq"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <BlynkSimpleEsp32.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

char ssid[] = "Guilherme2";
char pass[] = "walmeling12";

// Pinos dos relés
#define rele1 26
#define rele2 27

#define RELAY_ON  LOW
#define RELAY_OFF HIGH

// Configurações Sinric Pro
// Obtenha estes valores em: https://portal.sinric.pro
// Na seção "Credentials" você encontrará:
#define SINRICPRO_APP_KEY    "f7b4645c-6d0e-4df8-a6bc-a69f7f6bc56d"  // App Key (ou API Key)
#define SINRICPRO_APP_SECRET "443a9517-09c4-459d-a069-1d9e2b1a1436-e0bfe853-681d-459d-93cd-61e407f1ab89"  // App Secret (senha) - Cole aqui a senha que você obteve
#define SINRICPRO_DEVICE_ID_1 "6918af686ebb39d664b8ae1d"  // Device ID do Relé 1
#define SINRICPRO_DEVICE_ID_2 "6918afc7729a4887d7cef735"  // Device ID do Relé 2

BlynkTimer timer;
WebServer server(80);

// --- Função auxiliar para controlar relé e sincronizar todos os sistemas ---
void controlarRele(int rele, bool estado) {
  if (rele == 1) {
    digitalWrite(rele1, estado ? RELAY_ON : RELAY_OFF);
    Blynk.virtualWrite(V0, estado ? 1 : 0);
    // Sincroniza estado no Sinric Pro
    SinricProSwitch &mySwitch1 = SinricPro[SINRICPRO_DEVICE_ID_1];
    mySwitch1.sendPowerStateEvent(estado);
  } else if (rele == 2) {
    digitalWrite(rele2, estado ? RELAY_ON : RELAY_OFF);
    Blynk.virtualWrite(V1, estado ? 1 : 0);
    // Sincroniza estado no Sinric Pro
    SinricProSwitch &mySwitch2 = SinricPro[SINRICPRO_DEVICE_ID_2];
    mySwitch2.sendPowerStateEvent(estado);
  }
  atualizarStatus();
}

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
  controlarRele(1, value == 1);
}

BLYNK_WRITE(V1) {
  int value = param.asInt();
  controlarRele(2, value == 1);
}

// --- Botão "Tudo Off" via Blynk ---
BLYNK_WRITE(V4) {
  int value = param.asInt();

  if (value == 1) {
    Serial.println("Comando: Tudo Off");

    controlarRele(1, false);
    controlarRele(2, false);

    delay(300);
    Blynk.virtualWrite(V4, 0);
  }
}

// ==================== CALLBACKS SINRIC PRO ====================

// Callback para Relé 1 via Google Assistant
bool onPowerState1(const String &deviceId, bool &state) {
  Serial.printf("Sinric Pro - Relé 1: %s\r\n", state ? "ON" : "OFF");
  controlarRele(1, state);
  return true; // Confirma que o comando foi recebido
}

// Callback para Relé 2 via Google Assistant
bool onPowerState2(const String &deviceId, bool &state) {
  Serial.printf("Sinric Pro - Relé 2: %s\r\n", state ? "ON" : "OFF");
  controlarRele(2, state);
  return true; // Confirma que o comando foi recebido
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
  html += "<p style='margin-top:20px;color:#777;'>Sistema Integrado: Blynk + Sinric Pro (Google Assistant)</p>";
  html += "</body></html>";

  return html;
}

// --- Rotas do servidor ---
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

void handleOn1() {
  controlarRele(1, true);
  server.send(200, "text/html", getHTML());
}

void handleOff1() {
  controlarRele(1, false);
  server.send(200, "text/html", getHTML());
}

void handleOn2() {
  controlarRele(2, true);
  server.send(200, "text/html", getHTML());
}

void handleOff2() {
  controlarRele(2, false);
  server.send(200, "text/html", getHTML());
}

void handleAllOff() {
  controlarRele(1, false);
  controlarRele(2, false);
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

  // Configura Sinric Pro
  SinricProSwitch &mySwitch1 = SinricPro[SINRICPRO_DEVICE_ID_1];
  mySwitch1.onPowerState(onPowerState1);
  
  SinricProSwitch &mySwitch2 = SinricPro[SINRICPRO_DEVICE_ID_2];
  mySwitch2.onPowerState(onPowerState2);

  // Inicia Sinric Pro com App Key e App Secret
  SinricPro.begin(SINRICPRO_APP_KEY, SINRICPRO_APP_SECRET);
  Serial.println("Sinric Pro iniciado!");

  timer.setInterval(2000L, atualizarStatus);

  Serial.println("Sistema iniciado com sucesso!");
  Serial.println("Integrações ativas: Blynk + Web Local + Sinric Pro (Google Assistant)");
}

// --- Loop ---
void loop() {
  Blynk.run();
  SinricPro.handle();
  timer.run();
  server.handleClient();
}
