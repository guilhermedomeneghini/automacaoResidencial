# 💡 Automação Residencial com ESP32, Blynk e Interface Web Local

Este projeto demonstra um **sistema de automação residencial de baixo custo** utilizando o **ESP32**, com controle de **dois relés** (para acender/apagar dispositivos elétricos) integrado ao **Blynk Cloud** e a uma **interface web local (HTML)**, permitindo controle tanto via aplicativo quanto via navegador.

---

## 🚀 Funcionalidades

✅ Controle **remoto** dos relés via **Blynk Cloud** (app Blynk)  
✅ Controle **local** via navegador web (servidor HTTP interno no ESP32)  
✅ Botão “**Desligar Tudo**” que desativa todos os relés simultaneamente  
✅ Atualização **sincronizada** entre o Blynk e o painel HTML  
✅ Interface moderna, responsiva e leve  
✅ Conexão Wi-Fi automática com feedback no monitor serial  

---

## 🧠 Tecnologias Utilizadas

- **ESP32 (DOIT Devkit)**  
- **Blynk IoT Cloud**  
- **WebServer (ESP32 core)**  
- **C++ / Arduino IDE**  
- **HTML + CSS (gerado dinamicamente)**  

---

## ⚙️ Esquema de Ligação

| Módulo Relé | ESP32 | Função |
|:-------------|:------|:--------|
| VCC (ou DC+) | VIN (3V) | Alimentação do relé |
| GND          | GND     | Terra comum |
| IN1          | GPIO26  | Controle do relé 1 |
| IN2          | GPIO27  | Controle do relé 2 |

> 💡 O relé deve estar configurado em **modo LOW** (chave seletora no módulo)  
> Assim ele liga com sinal `LOW` e desliga com `HIGH`.

---

## 🌐 Interface Web Local

Após o upload, verifique no **Monitor Serial** o IP atribuído ao ESP32.  
Acesse o painel pelo navegador:


### 🔸 Recursos da página:
- Botões “Ligar” e “Desligar” para cada relé  
- Botão “Desligar Tudo”  
- Status atual dos relés  
- Design limpo e adaptável para celular e desktop  

---

## 📱 Integração com o Blynk

No **app Blynk**, configure os seguintes widgets virtuais:

| Widget | Pino Virtual | Função |
|:--------|:--------------|:---------|
| Botão 1 | V0 | Relé 1 |
| Botão 2 | V1 | Relé 2 |
| Display | V2 | Status geral |
| Botão “Tudo Off” | V4 | Desliga ambos os relés |

> A integração é **bidirecional** — qualquer alteração feita pelo app é refletida na página web, e vice-versa.

---

## 🧩 Estrutura do Código


Principais seções:
- **Wi-Fi + Blynk** → conexão e autenticação  
- **Controle dos relés** → comandos físicos e virtuais  
- **Servidor Web** → interface HTML  
- **Sincronização** → atualização entre app e web  

---

## 🧰 Requisitos

- [Arduino IDE](https://www.arduino.cc/en/software)
- Biblioteca **Blynk** (`BlynkSimpleEsp32.h`)
- Placa **ESP32** instalada no gerenciador de placas
- Módulo Relé 3.3V / 5V compatível com ESP32

---

## 🛠️ Configuração

1. No código, altere as credenciais:
   ```cpp
   char ssid[] = "SeuWiFi";
   char pass[] = "SuaSenha";
   #define BLYNK_AUTH_TOKEN "Seu_Token_Blynk"
