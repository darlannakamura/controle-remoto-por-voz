#include <IRremoteESP8266.h> //INCLUSÃO DE BIBLIOTECA  
#include <ESP8266WiFi.h> //INCLUSÃO DA BIBLIOTECA NECESSÁRIA PARA FUNCIONAMENTO WiFi
 
const char* ssid = "XT1068 9446"; //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
const char* password = "darlan123"; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR
 
WiFiServer server(8082); //CASO OCORRA PROBLEMAS COM A PORTA 80, UTILIZE OUTRA (EX:8082,8089)

IRsend irsend(14); //FUNÇÃO RESPONSÁVEL PELO MÉTODO DE ENVIO DO SINAL IR

int tamanho = 68; //TAMANHO DA LINHA RAW(68 BLOCOS)
int frequencia = 32; //FREQUÊNCIA DO SINAL IR(32KHz)

// BOTÃO ENTRADA
unsigned int ENTRADA[68] = {9050,4500,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,600,600,600,600,600,600,1700,600,600,600,600,600,600,600,600,600,1700,600,1700,600,1700,600,600,550,1700,600,1700,600,1700,550,1750,600};
// BOTÃO LIGA / DESLIGA
unsigned int LD[68] = {9050,4500,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,550,600,550,1750,550,1700,550,600,550,600,550,600,550,600,550,600,550,600,550,600,550,600,550,1750,550,1750,550,1700,550,1700,550,1750,550,1700,550,1700,550};
// BOTÃO UM
unsigned int UM[68] = {9050,4500,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,1700,600,600,600,1700,600,600,600,1700,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600};
// BOTÃO DOIS
unsigned int DOIS[68] = {9050,4500,600,550,600,550,650,550,600,550,650,500,600,550,650,500,600,550,600,1650,650,500,650,1650,600,1650,600,1650,600,1650,600,550,600,1650,600,550,600,1650,600,1650,600,550,600,1650,600,550,600,600,600,550,550,1700,550,600,550,600,550,1700,600,550,550,1700,550,1700,600,1700,550};
// BOTÃO TRES
unsigned int TRES[68] = {9050,4500,600,600,600,600,650,550,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,600,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600};
// BOTÃO QUATRO
unsigned int QUATRO[68] = {9050,4550,550,600,600,600,550,600,550,600,550,600,550,600,550,600,550,600,550,1700,600,550,550,1700,550,1700,550,1700,550,1700,550,600,550,1700,550,1700,550,600,550,600,550,1700,550,1700,550,600,600,600,550,600,550,600,550,1700,550,1700,550,600,600,600,600,1650,550,1700,550,1700,550};
// BOTÃO CINCO
unsigned int CINCO[68] = {9050,4500,600,600,550,600,600,600,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,550,1700,600,1700,600,600,600,1700,600,600,600,1700,600,600,600,1700,600,1700,600,600,600,600,600,600,600,1700,600,600,600,1700,600,600,600,600,600,1700,600,1700,550,1750,600};
// BOTÃO SEIS
unsigned int SEIS[68] = {9050,4550,600,550,600,550,600,600,550,600,550,600,550,600,550,600,550,600,600,1650,550,600,600,1650,550,1700,600,1700,600,1650,600,600,550,1700,550,1700,550,1700,600,550,600,1650,600,1650,600,600,550,600,550,600,550,600,600,600,550,1700,600,600,550,600,550,1700,600,1650,600,1700,600};
// BOTÃO SETE
unsigned int SETE[68] = {9050,4500,600,600,600,600,550,600,600,600,550,600,550,600,600,600,550,600,600,1700,600,600,550,1700,550,1700,600,1700,550,1700,550,600,550,1700,550,1700,550,600,600,1700,600,1700,550,1700,600,600,600,600,550,600,550,600,600,1700,550,600,550,600,550,600,600,1700,550,1700,550,1700,550};
// BOTÃO OITO
unsigned int OITO[68] = {9050,4500,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,600,600,600,600,1700,600,600,600,600,600,600,600,600,600,1700,600,1700,600,1700,600};
// BOTÃO NOVE
unsigned int NOVE[68] = {9050,4550,550,600,550,600,550,600,550,600,550,600,550,600,550,600,550,600,550,1700,550,600,550,1700,550,1700,550,1700,550,1700,550,600,550,1700,550,1700,550,1700,550,1700,550,1700,550,1700,550,600,550,600,550,600,550,600,550,600,550,600,550,600,550,600,600,1700,550,1700,550,1700,550};
// BOTÃO ZERO
unsigned int ZERO[68] = {9050,4550,600,550,550,600,600,550,600,550,600,550,550,600,600,550,550,600,600,1650,550,600,600,1650,600,1650,600,1650,600,1650,550,600,550,1700,600,1650,550,600,550,600,550,600,550,600,600,550,600,1650,600,550,600,550,600,1650,600,1650,550,1700,600,1650,600,1650,600,550,600,1650,600};
// BOTÃO PONTO
unsigned int PONTO[68] = {9050,4500,600,550,600,550,600,550,600,600,600,550,600,550,600,550,600,550,600,1700,600,550,600,1700,600,1700,600,1700,600,1700,600,550,600,1700,600,1700,600,1700,600,550,600,1700,600,550,600,550,600,1700,600,550,600,550,600,550,600,1700,600,550,600,1700,600,1700,600,550,600,1700,600};
// BOTÃO CIMA
unsigned int CIMA[68] = {9050,4500,600,600,600,600,600,600,600,600,600,600,600,550,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,1700,600,1700,600,600,600,1700,600,600,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600};
// BOTÃO BAIXO
unsigned int BAIXO[68] = {9050,4500,550,600,550,600,550,600,550,600,550,600,550,600,600,600,550,600,550,1700,550,600,550,1700,550,1700,550,1700,550,1700,550,600,550,1700,550,1700,550,1700,550,1700,550,1700,550,600,550,600,550,600,550,600,550,600,550,600,550,600,550,600,550,1700,550,1700,550,1700,550,1700,550};
// BOTÃO DIREITA
unsigned int DIREITA[68] = {9050,4550,550,600,600,600,550,600,550,600,600,600,600,600,600,600,550,600,550,1700,600,600,550,1700,550,1700,550,1700,550,1700,600,600,600,1700,550,600,600,1700,550,600,600,1700,550,600,600,600,550,1700,550,600,550,1700,550,600,550,1700,600,600,550,1700,550,1700,600,600,600,1700,600};
// BOTÃO ESQUERDA
unsigned int ESQUERDA[68] = {9050,4500,600,600,600,600,600,600,550,600,600,550,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,1700,550,600,550,600,600,1700,600,600,600,600,600,1700,600,600,600,600,600,1700,600,1700,550,600,600,1700,600,1700,600,600,600,1700,550};
// BOTÃO OK
unsigned int BOTAO_OK[68] = {9050,4500,600,600,600,600,600,600,550,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,1700,600,600,550,1700,600,1700,600,600,600,600,600,600,600,600,600,600,600,1700,550,600,600,600,600,1700,600,1700,600,1700,600,1700,600};
// BOTÃO MENU
unsigned int MENU[68] = {9050,4550,600,550,600,550,600,550,550,600,600,600,550,600,600,550,600,550,600,1650,600,550,600,1700,600,1650,600,1650,550,1700,550,600,550,1700,600,550,600,1650,600,550,600,1700,600,550,600,550,600,550,600,550,550,1700,600,550,550,1700,600,600,550,1700,600,1650,600,1650,600,1650,600};
// BOTÃO VOLTAR
unsigned int VOLTAR[68] = {9050,4500,550,600,600,600,600,600,600,600,600,600,600,600,550,600,600,600,600,1700,600,600,550,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,600,600,600,600,1700,600,600,600,600,600,600,550,1700,550,600,600,1700,600,1700,600,600,550,1700,600,1700,600,1700,600,600,550,1700,600};
// BOTÃO SAIR
unsigned int SAIR[68] = {9050,4550,550,600,550,600,550,600,550,600,550,600,550,600,600,600,550,600,600,1700,550,600,550,1700,550,1700,550,1700,550,1700,550,600,550,1700,600,1700,550,1700,550,1700,550,600,600,600,550,600,550,600,600,600,550,600,550,600,550,600,600,1700,550,1700,550,1700,550,1700,550,1700,550};
// BOTÃO AUMENTAR VOLUME
unsigned int VMAIS[68] = {9050,4500,650,500,600,550,600,550,650,500,600,550,600,550,600,550,600,550,650,1650,600,550,600,1650,650,1650,650,1650,600,1650,600,550,650,1650,600,550,650,500,600,1650,650,1650,600,550,600,550,600,550,600,550,650,1650,600,1650,600,550,650,500,600,1650,650,1650,650,1650,650,1650,650};
// BOTÃO DIMINUIR VOLUME
unsigned int VMENOS[68] = {9050,4500,600,550,600,550,600,550,600,550,600,550,600,550,650,550,600,550,600,1700,600,550,600,1650,650,1650,600,1650,650,1650,600,550,600,1650,600,550,650,500,600,550,600,550,600,1650,600,550,600,550,600,550,600,1650,600,1650,650,1650,600,1650,600,550,600,1650,600,1650,650,1650,600};
// BOTÃO MUTE
unsigned int MT[68] = {9050,4500,600,600,600,600,600,600,600,600,550,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,600,600,600,600,1700,600,600,600,600,600,600,600,600,600,600,600,1700,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,1700,600};
// BOTÃO AVANÇAR CANAL
unsigned int CMAIS[68] = {9050,4500,600,600,550,600,550,600,550,600,600,600,600,600,600,600,550,600,550,1700,550,600,600,1700,550,1700,600,1700,550,1700,600,600,550,1700,600,600,550,600,550,600,550,1700,600,1700,600,600,550,600,600,600,600,1700,600,1700,600,1700,600,600,550,600,600,1700,550,1700,550,1700,600};
// BOTÃO VOLTAR CANAL
unsigned int CMENOS[68] = {9050,4500,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,600,1700,600,600,600,1700,600,1700,600,1700,600,1700,600,600,600,1700,600,600,600,600,600,1700,600,1700,600,1700,600,600,600,600,600,600,600,1700,600,1700,600,600,600,600,600,600,600,1700,600,1700,600,1700,600};
//BOTÃO TIMER
unsigned int TIMER[68] = {9050,4550,550,600,600,600,550,600,550,600,550,600,550,600,550,600,600,550,550,1700,600,550,550,1700,550,1700,600,1700,600,1700,550,600,550,1700,600,1650,600,1700,550,600,550,600,550,1700,600,550,600,550,600,550,600,550,600,600,550,1700,600,1700,600,600,600,1650,600,1650,600,1650,600};

void setup() {
  // put your setup code here, to run once:
  irsend.begin(); //INICIALIZA A FUNÇÃO
  Serial.begin(115200); //INICIALIZA A PORTA SERIAL
  delay(100);
  Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
  Serial.print("Conectando a "); //ESCREVE O TEXTO NA SERIAL
  Serial.print(ssid); //ESCREVE O NOME DA REDE NA SERIAL
   
  WiFi.begin(ssid, password); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE SEM FIO
   
  while (WiFi.status() != WL_CONNECTED) { //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
  delay(500); //INTERVALO DE 500 MILISEGUNDOS
  Serial.print("."); //ESCREVE O CARACTER NA SERIAL
  }
  Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL
  Serial.print("Conectado a rede sem fio "); //ESCREVE O TEXTO NA SERIAL
  Serial.println(ssid); //ESCREVE O NOME DA REDE NA SERIAL
  server.begin(); //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA DEFINIDA EM "WiFiServer server(porta);"
  Serial.println("Servidor iniciado"); //ESCREVE O TEXTO NA SERIAL
   
  Serial.print("IP para se conectar ao NodeMCU: "); //ESCREVE O TEXTO NA SERIAL
  Serial.print("http://"); //ESCREVE O TEXTO NA SERIAL
  Serial.println(WiFi.localIP()); //ESCREVE NA SERIAL O IP RECEBIDO DENTRO DA REDE SEM FIO (O IP NESSA PRÁTICA É RECEBIDO DE FORMA AUTOMÁTICA)
  Serial.print("Mac address: ");
  Serial.println(WiFi.macAddress());
  Serial.println("");

  
  
}

void loop() {
  // put your main code here, to run repeatedly:  

  WiFiClient client = server.available(); //VERIFICA SE ALGUM CLIENTE ESTÁ CONECTADO NO SERVIDOR
  if (!client) { //SE NÃO EXISTIR CLIENTE CONECTADO, FAZ
    return; //REEXECUTA O PROCESSO ATÉ QUE ALGUM CLIENTE SE CONECTE AO SERVIDOR
  }
  Serial.println("Novo cliente se conectou!"); //ESCREVE O TEXTO NA SERIAL
  while(!client.available()){ //ENQUANTO CLIENTE ESTIVER CONECTADO
    delay(1); //INTERVALO DE 1 MILISEGUNDO
  }
  String request = client.readStringUntil('\r'); //FAZ A LEITURA DA PRIMEIRA LINHA DA REQUISIÇÃO
  Serial.println(request); //ESCREVE A REQUISIÇÃO NA SERIAL

  request = request.substring(request.indexOf('/') + 1);  // Já pega do início do comando
  String comando = request.substring(0, request.indexOf(' '));  // Corta após o fim do comando

  Serial.println(comando);
  Serial.println(comando.length());

  if (comando.equals("entradas") || comando.equals("input") || comando.equals("entrada")){
    irsend.sendRaw(ENTRADA,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("ligar") || comando.equals("desligar")){
    irsend.sendRaw(LD,tamanho,frequencia);
    delay(50);    
  }
  else if(comando.equals("1")) {
    irsend.sendRaw(UM,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("2")) {
    irsend.sendRaw(DOIS,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("3")) {
    irsend.sendRaw(TRES,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("4")) {
    irsend.sendRaw(QUATRO,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("5")) {
    irsend.sendRaw(CINCO,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("6")) {
    irsend.sendRaw(SEIS,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("7")) {
    irsend.sendRaw(SETE,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("8")) {
    irsend.sendRaw(OITO,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("9")) {
    irsend.sendRaw(NOVE,tamanho,frequencia);
    delay(50);
  }
  else if(comando.equals("0")) {
    irsend.sendRaw(ZERO,tamanho,frequencia);
    delay(50);
  }
  else if (comando.equals("traço") || comando.equals("ponto")){
    irsend.sendRaw(PONTO,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("cima")){
    irsend.sendRaw(CIMA,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("baixo")){
    irsend.sendRaw(BAIXO,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("direita")){
    irsend.sendRaw(DIREITA,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("esquerda")){
    irsend.sendRaw(ESQUERDA,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("ok")){
    irsend.sendRaw(BOTAO_OK,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("menu")){
    irsend.sendRaw(MENU,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("voltar")){
    irsend.sendRaw(VOLTAR,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("sair")){
    irsend.sendRaw(SAIR,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("aumentarvolume")){
    irsend.sendRaw(VMAIS,tamanho,frequencia);
    delay(800); 
    irsend.sendRaw(VMAIS,tamanho,frequencia);
    delay(50);    
  }
  else if (comando.equals("diminuirvolume")){
    irsend.sendRaw(VMENOS,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(VMENOS,tamanho,frequencia);
    delay(50);    
  }
  else if (comando.equals("mudo")){
    irsend.sendRaw(MT,tamanho,frequencia);
    delay(50);  
  }
  else if (comando.equals("proximocanal")){
    irsend.sendRaw(CMAIS,tamanho,frequencia);
    delay(50);    
  }
  else if (comando.equals("voltarcanal")){
    irsend.sendRaw(CMENOS,tamanho,frequencia);
    delay(50);    
  }
  else if (comando.equals("globo")){
    irsend.sendRaw(TRES,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(UM,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(PONTO,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(UM,tamanho,frequencia);
    delay(50);
  }
  else if (comando.equals("band")){
    irsend.sendRaw(UM,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(ZERO,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(PONTO,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(UM,tamanho,frequencia);
    delay(50);
  }
  else if (comando.equals("sbt")){
    irsend.sendRaw(QUATRO,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(PONTO,tamanho,frequencia);
    delay(800);
    irsend.sendRaw(UM,tamanho,frequencia);
    delay(50);
  }
  else{
      if (comando.substring(0,8).equals("aumentar")) {
        int indice_hifen = comando.indexOf("-");
        int quantidade = comando.substring(indice_hifen+1).toInt();
        Serial.println("Aumentar Volume");
        Serial.println(quantidade);
        irsend.sendRaw(VMAIS,tamanho,frequencia);
        delay(800); 
        for (int i=0; i<quantidade; i++){
          irsend.sendRaw(VMAIS,tamanho,frequencia);
          delay(800);
        }
      }
      else if (comando.substring(0,8).equals("diminuir")) {
        int indice_hifen = comando.indexOf("-");
        int quantidade = comando.substring(indice_hifen+1).toInt();
        irsend.sendRaw(VMENOS,tamanho,frequencia);
        delay(800); 
        for (int i=0; i<quantidade; i++){
          irsend.sendRaw(VMENOS,tamanho,frequencia);
          delay(800);
        }
      }
      else if (comando.substring(0,5).equals("timer")){
        String minutos = comando.substring(comando.indexOf("-")+1);
        irsend.sendRaw(TIMER,tamanho,frequencia);
        delay(800);
        if (minutos.equals("10")) {
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(50);
        }
        else if(minutos.equals("20")) {
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(50);
        }
        else if (minutos.equals("30")) {
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(50);
        }
        else if (minutos.equals("60")) {
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(50);
        }
        else if (minutos.equals("120")) {
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(800);
          irsend.sendRaw(TIMER,tamanho,frequencia);
          delay(50);
        }
    }
  }




  
  client.flush(); //AGUARDA ATÉ QUE TODOS OS DADOS DE SAÍDA SEJAM ENVIADOS AO CLIENTE
   
  client.println("HTTP/1.1 200 OK"); //ESCREVE PARA O CLIENTE A VERSÃO DO HTTP
  client.println("Content-Type: text/html"); //ESCREVE PARA O CLIENTE O TIPO DE CONTEÚDO(texto/html)
  client.println("");
  client.println("<!DOCTYPE HTML>"); //INFORMA AO NAVEGADOR A ESPECIFICAÇÃO DO HTML
  client.println("<html>"); //ABRE A TAG "html"
  client.println("<h1><center>Ola cliente!</center></h1>"); //ESCREVE "Ola cliente!" NA PÁGINA
  client.println("<center><font size='5'>Seja bem vindo!</center>"); //ESCREVE "Seja bem vindo!" NA PÁGINA
  client.println("</html>"); //FECHA A TAG "html"
  delay(1); //INTERVALO DE 1 MILISEGUNDO
  Serial.println("Cliente desconectado"); //ESCREVE O TEXTO NA SERIAL
  Serial.println(""); //PULA UMA LINHA NA JANELA SERIAL


  
  
}
