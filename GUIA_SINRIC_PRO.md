# Guia Completo: Configurar Sinric Pro para Google Assistant

Este guia mostra como configurar o Sinric Pro para controlar seus relés via Google Assistant, **sem precisar de servidor próprio ou pagar nada**.

## 🎯 O que é Sinric Pro?

Sinric Pro é um serviço **gratuito** que conecta seus dispositivos IoT (ESP32) diretamente ao Google Assistant e Alexa, sem necessidade de servidor intermediário.

## 📋 Pré-requisitos

1. ✅ ESP32 com código atualizado
2. ✅ Conta Google
3. ✅ Conexão Wi-Fi

## 🚀 Passo a Passo

### Passo 1: Criar Conta no Sinric Pro

1. Acesse: **https://portal.sinric.pro/**
2. Clique em **"Sign Up"** ou **"Sign In"**
3. Crie sua conta (pode usar conta Google)
4. Confirme seu email se necessário

### Passo 2: Criar Dispositivos

1. Após fazer login, você verá o dashboard
2. Clique em **"Devices"** no menu lateral
3. Clique em **"+ Add Device"**

#### Criar Relé 1:
- **Device Name**: `Rele 1` (ou qualquer nome que preferir)
- **Device Type**: Selecione **"Switch"**
- **Room**: Escolha ou crie uma sala (ex: "Sala", "Quarto")
- Clique em **"Save"**
- **Anote o Device ID** que será gerado (ex: `60d5f49bff906605e8f27a94`)

#### Criar Relé 2:
- Repita o processo acima
- **Device Name**: `Rele 2`
- **Device Type**: **"Switch"**
- **Anote o Device ID** do segundo dispositivo

### Passo 3: Obter Credenciais (App Key e App Secret)

1. No menu lateral, clique em **"Credentials"**
2. Você verá:
   - **App Key** (ou API Key) - ex: `a1b2c3d4-e5f6-7890-abcd-ef1234567890`
   - **App Secret** (senha) - ex: `senha1234567890abcdef`
3. **Copie e anote** ambos os valores
   - O App Key é a chave de acesso
   - O App Secret é a senha de autenticação

### Passo 4: Configurar o Código Arduino

1. Abra o arquivo `automacao.ino` no Arduino IDE
2. Localize as linhas:

```cpp
#define SINRICPRO_APP_KEY    "SUA_APP_KEY_AQUI"
#define SINRICPRO_APP_SECRET "SUA_APP_SECRET_AQUI"
#define SINRICPRO_DEVICE_ID_1 "DEVICE_ID_RELE1"
#define SINRICPRO_DEVICE_ID_2 "DEVICE_ID_RELE2"
```

3. Substitua pelos valores que você anotou:

```cpp
#define SINRICPRO_APP_KEY    "a1b2c3d4-e5f6-7890-abcd-ef1234567890"
#define SINRICPRO_APP_SECRET "senha1234567890abcdef"
#define SINRICPRO_DEVICE_ID_1 "60d5f49bff906605e8f27a94"
#define SINRICPRO_DEVICE_ID_2 "60d5f49bff906605e8f27a95"
```

### Passo 5: Instalar Biblioteca Sinric Pro

1. No Arduino IDE, vá em **Sketch > Include Library > Manage Libraries**
2. Procure por: **"Sinric Pro"**
3. Instale a biblioteca **"SinricPro"** (por Mathias Munk Hansen)
4. Aguarde a instalação terminar

### Passo 6: Fazer Upload do Código

1. Conecte seu ESP32 ao computador
2. Selecione a placa: **Tools > Board > ESP32 Dev Module** (ou sua placa)
3. Selecione a porta: **Tools > Port**
4. Clique em **Upload**
5. Abra o **Serial Monitor** (115200 baud) para ver os logs

### Passo 7: Conectar ao Google Assistant

1. No portal Sinric Pro, vá em **"Integrations"**
2. Clique em **"Google"**
3. Clique em **"Link Account"**
4. Faça login com sua conta Google
5. Autorize o Sinric Pro a acessar sua conta
6. Aguarde a confirmação

### Passo 8: Testar

Agora você pode usar comandos de voz:

- **"Ok Google, ligar Relé 1"**
- **"Ok Google, desligar Relé 1"**
- **"Ok Google, ligar Relé 2"**
- **"Ok Google, desligar Relé 2"**

Ou pelo app Google Home:
1. Abra o app **Google Home**
2. Seus dispositivos aparecerão automaticamente
3. Toque para ligar/desligar

## 🔧 Solução de Problemas

### ESP32 não conecta ao Sinric Pro

**Verifique:**
- ✅ App Key está correta (sem espaços extras)
- ✅ App Secret (senha) está correta
- ✅ Device IDs estão corretos
- ✅ Wi-Fi está funcionando
- ✅ Serial Monitor mostra mensagens de conexão

**No Serial Monitor você deve ver:**
```
Wi-Fi conectado!
Sinric Pro iniciado!
```

### Google Assistant não encontra os dispositivos

**Solução:**
1. No portal Sinric Pro, vá em **"Integrations" > "Google"**
2. Clique em **"Unlink"** e depois **"Link Account"** novamente
3. Aguarde alguns minutos para sincronizar
4. No app Google Home, faça **"Refresh"** ou reinicie o app

### Dispositivos aparecem com nomes estranhos

**Solução:**
1. No portal Sinric Pro, vá em **"Devices"**
2. Clique no dispositivo
3. Altere o **"Device Name"** para algo mais amigável
4. Salve e aguarde alguns minutos

### Comandos não funcionam

**Verifique:**
- ✅ ESP32 está ligado e conectado ao Wi-Fi
- ✅ No portal Sinric Pro, os dispositivos aparecem como **"Online"**
- ✅ Serial Monitor mostra mensagens quando você dá comandos
- ✅ Tente usar o app Google Home primeiro para testar

## 📱 Usando o App Google Home

1. Baixe o app **Google Home** no seu celular
2. Faça login com a mesma conta Google
3. Os dispositivos do Sinric Pro aparecerão automaticamente
4. Você pode:
   - Ligar/desligar tocando nos botões
   - Criar rotinas
   - Adicionar aos seus grupos de dispositivos

## 🎤 Comandos de Voz

Você pode usar várias variações:

- "Ok Google, ligar Relé 1"
- "Ok Google, acender Relé 1"
- "Ok Google, ativar Relé 1"
- "Ok Google, desligar Relé 1"
- "Ok Google, apagar Relé 1"

O Google Assistant reconhece o nome que você deu ao dispositivo no Sinric Pro.

## 🔄 Sincronização

O sistema está configurado para sincronizar automaticamente:

- ✅ **Blynk** ↔ **Sinric Pro** ↔ **Web Local**
- Quando você controla por qualquer método, todos os outros são atualizados
- O estado sempre fica sincronizado

## 📊 Monitoramento

No portal Sinric Pro:
- **Dashboard**: Veja estatísticas de uso
- **Devices**: Veja status online/offline
- **Logs**: Veja histórico de comandos

## 💡 Dicas

1. **Nomes dos dispositivos**: Use nomes simples e fáceis de pronunciar
2. **Rooms**: Organize seus dispositivos em salas para facilitar
3. **Rotinas**: Crie rotinas no Google Home para controlar múltiplos dispositivos
4. **Backup**: Anote seus Device IDs, App Key e App Secret em local seguro

## 🆓 Limites Gratuitos

O plano gratuito do Sinric Pro permite:
- ✅ Até 5 dispositivos
- ✅ Uso ilimitado
- ✅ Google Assistant e Alexa
- ✅ Sem necessidade de servidor próprio

## 📞 Suporte

- **Documentação Sinric Pro**: https://sinricpro.github.io/
- **Portal**: https://portal.sinric.pro/
- **Comunidade**: GitHub do Sinric Pro

---

**Pronto!** Agora você tem controle completo via Google Assistant, mantendo todas as funcionalidades do Blynk e Web Local! 🎉

