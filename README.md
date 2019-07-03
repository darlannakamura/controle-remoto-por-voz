# Controle Remoto Por Voz
Trabalho da disciplina de FPGA do Curso de Ciência da Computação da FCT-Unesp, campus de Presidente Prudente. 

Este projeto é um protótipo do funcionamento de controle remoto por voz, onde utilizamos o aplicativo desenvolvido em React Native, que está dentro da pasta `app` para receber o comando do usuário por voz e enviar uma requisição HTTP para o servidor do Node MCU, que o código está disponível na pasta `nodemcu`. O servidor em Node MCU recebe o comando e o executa, enviando o sinal infra-vermelho para a televisão.


# Introdução
Desenvolvemos uma aplicação específica para Android (testado com o Android na versão 6.0), capaz de receber o comando por voz, processar e enviar uma requisição para o Node MCU. Foi utilizado a tecnologia React Native, capaz de transpilar códigos Javascript para a linguagem nativa, além de prover todo uma plataforma para facilitar o desenvolvimento. Para a conversão de comandos de voz para texto (speech to text), utilizamos a biblioteca chamada react-native-voice (versão 0.2.6). Para retornar a interação e em erros do usuário, usamos uma biblioteca chamada react-native-tts (versão 3.0.0), responsável por realizar o text to speech, dessa forma, quando o usuário erra algum comando, retornamos por meio de áudio que não reconhecemos o comando.


# Configuração

## Instalação

É importante realizar a instalação sem o Expo, pois o aplicativo utiliza recursos nativos do android, sendo necessário o acesso à pasta `android` (em que não é possível com o expo), sendo o tutorial para a instalação através do link: https://facebook.github.io/react-native/docs/getting-started.html.

## Setup
- Clone o projeto executando o comando: `git clone https://github.com/darlannakamura/speech.git`
- Navegue pelo terminal até a pasta clonada.
- Execute o comando `npm install` para instalar as dependências listadas no arquivo `package.json`.
- No arquivo `App.js`, na linha 109, injetamos diretamente o IP e a porta do servidor Node MCU na rede. Uma recomendação é remover o IP e a porta e adicionar para o arquivo de configuração, para o código ficar mais bonito.

## Inicializar o aplicativo e o ambiente de desenvolvimento
Para iniciar o aplicativo, é preciso que o celular com Android esteja conectado à maquina. Para isso, “plugue” um cabo USB ao celular. Após garantir que o celular está conectado, navegue até a pasta do projeto e execute o comando: “react-native run-android”. Este comando é responsável por gerar o `debug.apk` e instalá-lo no dispositivo (este comando demora alguns minutos, tenha paciência!). 

Após executá-lo, verá que qualquer atualização no código-fonte da aplicação irá atualizar automaticamente o aplicativo, agilizando muito o processo de desenvolvimento. Caso não atualize, você pode agitar o celular com o aplicativo aberto e irá abrir o menu com as opções. A primeira opção chama-se “Reload”.

## Dicas
- O celular e o computador precisam estar na mesma rede (utilizamos uma roteador móvel do celular, pois é difícil conectar o Node MCU na rede da Unesp).
- Utilize o `remote debugger`: agite o celular, abra o menu, e escolha a opção “Remote Debugger”.

# Autores
- [Darlan Nakamura](https://github.com/darlannakamura)
- [Rafael Bezerra](https://github.com/RafaelBMR)
