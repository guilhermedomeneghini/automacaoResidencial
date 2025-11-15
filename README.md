# 💡 Automação Residencial com ESP32, Blynk, Web Local e Google Assistant

Este projeto demonstra um **sistema de automação residencial de baixo custo** utilizando o **ESP32**, com controle de **dois relés** (para acender/apagar dispositivos elétricos) integrado ao **Blynk Cloud**, a uma **interface web local (HTML)** e ao **Google Assistant via Sinric Pro**, permitindo controle via aplicativo, navegador e comandos de voz.

---

## 🚀 Funcionalidades

✅ Controle **remoto** dos relés via **Blynk Cloud** (app Blynk)  
✅ Controle **local** via navegador web (servidor HTTP interno no ESP32)  
✅ Controle por **voz** via **Google Assistant** (sem servidor próprio, 100% gratuito)  
✅ Botão "**Desligar Tudo**" que desativa todos os relés simultaneamente  
✅ Atualização **sincronizada** entre Blynk, Web Local e Google Assistant  
✅ Interface moderna, responsiva e leve  
✅ Conexão Wi-Fi automática com feedback no monitor serial  

---

## 🧠 Tecnologias Utilizadas

- **ESP32 (DOIT Devkit)**  
- **Blynk IoT Cloud**  
- **Sinric Pro** (integração Google Assistant gratuita)  
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

```
http://IP_DO_ESP32
```

### 🔸 Recursos da página:
- Botões "Ligar" e "Desligar" para cada relé  
- Botão "Desligar Tudo"  
- Status atual dos relés atualizado em tempo real  
- Design limpo e adaptável para celular e desktop  
- Sincronização automática com Blynk e Google Assistant  

---

## 📱 Integração com o Blynk

No **app Blynk**, configure os seguintes widgets virtuais:

| Widget | Pino Virtual | Função |
|:--------|:--------------|:---------|
| Botão 1 | V0 | Relé 1 |
| Botão 2 | V1 | Relé 2 |
| Display | V2 | Status geral |
| Botão "Tudo Off" | V4 | Desliga ambos os relés |

> A integração é **bidirecional** — qualquer alteração feita pelo app é refletida na página web e no Google Assistant, e vice-versa.

---

## 🗣️ Integração com Google Assistant (Sinric Pro)

Controle seus relés por **comandos de voz** usando o Google Assistant, sem precisar de servidor próprio ou pagar nada!

### 🔸 Como usar:

1. **Configure o Sinric Pro** (veja guia completo: [GUIA_SINRIC_PRO.md](GUIA_SINRIC_PRO.md))
2. **Conecte sua conta Google** no portal Sinric Pro
3. **Use comandos de voz:**

   - "Ok Google, ligar Relé 1"
   - "Ok Google, desligar Relé 1"
   - "Ok Google, ligar Relé 2"
   - "Ok Google, desligar Relé 2"

### 🔸 Vantagens:

- ✅ **100% Gratuito** - Sem custos ou servidor próprio
- ✅ **Fácil configuração** - Apenas alguns passos
- ✅ **Sincronização automática** - Estado sempre atualizado
- ✅ **Funciona com Google Home** - Controle pelo app também

> 📖 **Guia completo de configuração:** [GUIA_SINRIC_PRO.md](GUIA_SINRIC_PRO.md)

---

## 🔄 Sincronização entre Plataformas

O sistema mantém **sincronização automática** entre todas as plataformas:

```
┌─────────────┐
│   Blynk     │
└──────┬──────┘
       │
       ├──────────────┐
       │              │
┌──────▼──────┐  ┌────▼──────┐
│  Web Local  │  │  Google   │
│             │  │ Assistant │
└─────────────┘  └───────────┘
       │              │
       └──────┬──────┘
              │
       ┌──────▼──────┐
       │    ESP32    │
       │  (Relés)    │
       └─────────────┘
```

**Qualquer controle** feito em uma plataforma é **automaticamente refletido** nas outras!

---

## 🧩 Estrutura do Código

Principais seções:
- **Wi-Fi + Blynk** → conexão e autenticação  
- **Sinric Pro** → integração Google Assistant  
- **Controle dos relés** → comandos físicos e virtuais sincronizados  
- **Servidor Web** → interface HTML  
- **Sincronização** → atualização entre app, web e Google Assistant  

---

## 🧰 Requisitos

### Hardware
- **ESP32** (DOIT Devkit ou similar)
- **2x Módulo Relé** 3.3V / 5V compatível com ESP32
- Fonte de alimentação adequada
- Conexão Wi-Fi

### Software
- [Arduino IDE](https://www.arduino.cc/en/software)
- Bibliotecas:
  - **BlynkSimpleESP32** (via Library Manager)
  - **SinricPro** (via Library Manager)
- Placa **ESP32** instalada no gerenciador de placas

### Contas Necessárias
- Conta **Blynk** (gratuita) - https://blynk.io
- Conta **Sinric Pro** (gratuita) - https://portal.sinric.pro
- Conta **Google** (para Google Assistant)

---

## 🛠️ Configuração

### 1. Instalar Bibliotecas

No Arduino IDE:
- **Sketch > Include Library > Manage Libraries**
- Procure e instale:
  - `BlynkSimpleESP32`
  - `SinricPro`

### 2. Configurar Credenciais

No código `automacao.ino`, altere as credenciais:

```cpp
// Wi-Fi
char ssid[] = "SeuWiFi";
char pass[] = "SuaSenha";

// Blynk
#define BLYNK_AUTH_TOKEN "Seu_Token_Blynk"

// Sinric Pro (obtenha em https://portal.sinric.pro)
#define SINRICPRO_APP_KEY "Sua_App_Key"
#define SINRICPRO_APP_SECRET "Sua_App_Secret"
#define SINRICPRO_DEVICE_ID_1 "Device_ID_Rele1"
#define SINRICPRO_DEVICE_ID_2 "Device_ID_Rele2"
```

### 3. Configurar Blynk

1. Crie uma conta em https://blynk.io
2. Crie um novo projeto
3. Adicione widgets:
   - **Button** no pino virtual **V0** (Relé 1)
   - **Button** no pino virtual **V1** (Relé 2)
   - **Label** no pino virtual **V2** (Status)
   - **Button** no pino virtual **V4** (Tudo Off)
4. Copie o **Auth Token** e cole no código

### 4. Configurar Sinric Pro

Siga o guia completo: **[GUIA_SINRIC_PRO.md](GUIA_SINRIC_PRO.md)**

**Resumo rápido:**
1. Crie conta em https://portal.sinric.pro
2. Crie 2 dispositivos tipo "Switch"
3. Copie **App Key**, **App Secret** e **Device IDs** (em "Credentials")
4. Cole no código
5. Conecte ao Google Assistant no portal

### 5. Fazer Upload

1. Conecte o ESP32 ao computador
2. Selecione a placa: **Tools > Board > ESP32 Dev Module**
3. Selecione a porta: **Tools > Port**
4. Clique em **Upload**
5. Abra o **Serial Monitor** (115200 baud) para ver os logs

---

## 📊 Monitor Serial

Após o upload, você verá no Serial Monitor:

```
Conectando ao Wi-Fi...
Wi-Fi conectado!
Endereço IP: 192.168.1.100
Sinric Pro iniciado!
Sistema iniciado com sucesso!
Integrações ativas: Blynk + Web Local + Sinric Pro (Google Assistant)
```

---

## 🔧 Solução de Problemas

### ESP32 não conecta ao Wi-Fi
- Verifique SSID e senha
- Certifique-se que o Wi-Fi é **2.4GHz** (ESP32 não suporta 5GHz)

### Blynk não conecta
- Verifique o Auth Token
- Confirme que o Wi-Fi está funcionando
- Veja os logs no Serial Monitor

### Sinric Pro não conecta
- Verifique App Key e App Secret
- Confirme Device IDs estão corretos
- Veja Serial Monitor para mensagens de erro
- Consulte [GUIA_SINRIC_PRO.md](GUIA_SINRIC_PRO.md)

### Google Assistant não encontra dispositivos
- No portal Sinric Pro, desvincule e vincule novamente a conta Google
- Aguarde alguns minutos para sincronizar
- Reinicie o app Google Home

### Erro ao fazer upload
- Pressione o botão **BOOT** do ESP32 durante o upload
- Verifique se a porta está correta
- Tente reduzir a velocidade de upload (Tools > Upload Speed)

---

## 📚 Documentação Adicional

- **[GUIA_SINRIC_PRO.md](GUIA_SINRIC_PRO.md)** - Guia completo de configuração do Google Assistant
- **[RESUMO_MELHORIAS.md](RESUMO_MELHORIAS.md)** - Resumo das melhorias implementadas

---

## 🎯 Formas de Controle

| Método | Como Usar | Vantagens |
|:-------|:---------|:----------|
| **Blynk App** | Abra o app e toque nos botões | Controle remoto de qualquer lugar |
| **Web Local** | Acesse `http://IP_ESP32` no navegador | Interface simples, sem app |
| **Google Assistant** | "Ok Google, ligar Relé 1" | Controle por voz, hands-free |

---

## 🔒 Segurança

⚠️ **Importante:**
- Não compartilhe suas credenciais (tokens, senhas)
- Use senhas fortes para Wi-Fi
- Mantenha o código atualizado
- Para produção, considere usar variáveis de ambiente

---

## 📄 Licença

Este projeto é fornecido como está, para uso pessoal e educacional.

---

## 🤝 Contribuições

Sinta-se à vontade para melhorar e adaptar este código às suas necessidades!

---

**Desenvolvido para automação residencial completa** 🏠✨

**Integrações:** Blynk + Web Local + Sinric Pro (Google Assistant)
