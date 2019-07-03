/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow
 */

import React, {Component} from 'react';
import {Platform, StyleSheet, Text, View, AppState} from 'react-native';
import Voice from 'react-native-voice';
import { Button } from 'react-native';
import { PermissionsAndroid } from 'react-native';
import Tts from 'react-native-tts';

// const instructions = Platform.select({
//   ios: 'Press Cmd+R to reload,\n' + 'Cmd+D or shake for dev menu',
//   android:
//     'Double tap R on your keyboard to reload,\n' +
//     'Shake or press menu button for dev menu',
// });

type Props = {};
export default class App extends Component<Props> {
  constructor(props) {
    super();
    
    Voice.onSpeechStart = this.onSpeechStartHandler.bind(this);
    Voice.onSpeechEnd = this.onSpeechEndHandler.bind(this);
    Voice.onSpeechResults = this.onSpeechResultsHandler.bind(this);

    startSpeech = this.startSpeech.bind(this);
    endSpeech = this.endSpeech.bind(this);

    this.state = { 
      text : '', 
      textButton: 'FALAR',
      isListening: false
    }; 
  }

  async componentDidMount() {
    AppState.addEventListener('change', this._handleAppStateChange);
    await this.requestVoiceRecord();

    await this.startSpeech();
  }

  componentWillUnmount() {
    AppState.removeEventListener('change', this._handleAppStateChange);
    Tts.setDefaultLanguage('pt-BR');
  }

  _handleAppStateChange = async (nextAppState) => {
    await this.startSpeech();
  }

  async requestVoiceRecord() {
    try {
    
      const granted = await PermissionsAndroid.request(
        PermissionsAndroid.PERMISSIONS.RECORD_AUDIO, 
        {
          title: 'titulo',
          message: 'mensagem',
          buttonNeutral: 'Ask me later',
          buttonNegative: 'Cancel',
          buttonPositive: 'OK'
        }
      );

      if (granted === PermissionsAndroid.RESULTS.GRANTED) {
        console.log('You can use the record audio');
      } else {
        console.log('record audio permission denied');
      }

    } catch (err) {
      console.warn(err);
    }
  }

  async startSpeech() {
    try{
      await Voice.start('pt-BR');
    } catch(e) {
      console.log(e);
    }
  }

  async endSpeech() {
    try {
      await Voice.stop();
    } catch (e) {
      console.log(e);
    }
  }


  onSpeechEndHandler() {
    console.log('parou');
    this.setState({
      isListening: false,
      textButton: 'FALAR'
    });
  }

  sendRequest(url) {
    fetch(`http://192.168.43.221:8082/${url}`, 
      {method: 'GET', headers: {}, mode: 'cors', cache: 'default'}
      )
        .then( (res) => {
          // alert(`Enviou ${url}!`);
          console.log('Response:');
          console.log(res);
        });
  }

  _returnCommandRecognizedInTheText(text, commands) {

    let returnCommand = null;

    commands.forEach( command => {
      
      let  isString = (typeof(command.speech) == "string");

      if (isString && (text.includes(command.speech) || text == command.speech)) {
        returnCommand = command;
      } else { //command.speech is a Array. We can ensure this using Array.isArray(command.speech)
        if(Array.isArray(command.speech)) {
            
            command.speech.forEach( s => {
              if (text.includes(s)){
                returnCommand = command;
                console.log('entrou aqui');
                console.log(returnCommand);
              }
            });
        }
      }
    });
    
    if(returnCommand != null){
      return returnCommand;
    } else {
      return false;
    }

  }

  _returnMessage(message) {
    Tts.speak(message,
    { androidParams: { KEY_PARAM_PAN: -1, KEY_PARAM_VOLUME: 1, KEY_PARAM_STREAM: 'STREAM_MUSIC' } });
  }

  _getCommandList(){
    return [
      {
        speech: ['ligar', 'ativar'], 
        action: 'ligar'
      },
      {
        speech: 'canal',
        action: 'canal',
        commandClass: 'channel'
      },
      {
        speech: ['desligar', 'desconectar'], 
        action: 'desligar'
      },
      {
        speech: ['aumentar volume', 'elevar volume', 'ampliar volume'], 
        action: 'aumentarvolume',
        commandClass: 'volume'
      },
      {
        speech: ['abaixar volume', 'diminuir volume', 'minimizar volume', 'baixar volume'], 
        action: 'diminuirvolume',
        commandClass: 'volume'
      },
      {
        speech: ['trocar canal', 'aumentar canal', 'próximo canal'],
        action: 'proximocanal'
      },
      {
        speech: ['diminuir canal', 'retroceder canal', 'canal anterior', 'voltar canal'],
        action: 'voltarcanal'
      },
      {
        speech: 'cima', 
        action: 'cima'
      },
      {
        speech: 'baixo', 
        action: 'baixo'
      },
      {
        speech: ['ok', 'enter', 'inter'], 
        action: 'ok'
      },
      {
        speech: 'esquerda', 
        action: 'esquerda'
      },
      {
        speech: 'direita', 
        action: 'direita'
      },
      {
        speech: ['entrada', 'input', 'entradas'],
        action: 'entrada'
      },
      {
        speech: ['mudo', 'mute', 'muta'],
        action: 'mudo'
      },
      {
        speech: ['ponto', 'traço'], 
        action: 'ponto'
      },
      {
        speech: 'voltar',
        action: 'voltar'
      },
      {
        speech: 'sair',
        action: 'sair'
      },
      {
        speech: 'menu',
        action: 'menu'
      },
      {
        speech: ['timer', 'tempo pra desligar'], 
        action: 'timer',
        commandClass: 'timer'
      },
      {
        speech: 'band', 
        action: 'band'
      },
      {
        speech: 'globo', 
        action: 'globo'
      },
      {
        speech: 'parar',
        action: '',
        commandClass: 'stopApplication'
      }
    ];
  }

  _extractDigitsFromSentence(text){
    let num = text.match(/\d/g);
    if(num != null){
      let digit = num.join("");
      if(digit != ""){
        return parseInt(digit);
      } else {
        return 1;
      }
    } else {
      return 1;
    }
  } 

  _extractDigitsAndDotsFromSentence(text){
    let num = text.replace(/[^\d\.]*/g, '');
    return num;
  }

  _extractTimeFromSentence(text){
    const timing = [
      {
        text: "meia hora",
        value: 30
      },
      {
        text: "1 hora",
        value: 60
      },
      {
        text: "uma hora",
        value: 60
      },
      {
        text: "2 horas",
        value: 120
      },
      {
        text: "duas horas",
        value: 120
      }
    ];

    let returnValue = null;

    timing.forEach( e => {
      if(text.includes(e.text)) returnValue = e.value;
    });

    if(returnValue != null) return returnValue;

    return this._extractDigitsFromSentence(text);

  }

  _boundOfVolume(volume){
    if(volume < 0){
      return 0;
    } else{
      if (volume > 50){
        return 50;
      }
    }

    return volume;
  }

  async onSpeechResultsHandler(e) {
    let stopListening = false;
    
    let text = e.value[0];

    this.setState({
      text
    });

    let commands = [];

    for(let i = 0; i < 10; i++){
      commands.push({
        speech: ''+i,
        action: ''+i
      });
    }

    commands = commands.concat(this._getCommandList());


    let command = this._returnCommandRecognizedInTheText(text.toLowerCase(), commands);

    if (command == false){
      this._returnMessage("Não reconheci nenhum comando.");
    } else {
      if('commandClass' in command){
        if(command.commandClass == 'volume'){

          let volume = this._extractDigitsFromSentence(text);
          
          volume = this._boundOfVolume(volume); // para ficar entre o intervalo de 0 a 50.

          this.sendRequest(`${command.action}-${volume}`);
        } else if (command.commandClass == 'channel'){
          let channel = this._extractDigitsAndDotsFromSentence(text);
          
          for(let i = 0 ; i < channel.length; i++){
            let send = channel[i];
            
            if (send == '.'){
              send = 'ponto';
            }

            setTimeout(this.sendRequest(send),1000);
          }

        } else if (command.commandClass == 'timer') {
          let time = this._extractTimeFromSentence(text); //in minutes

          const acceptedValues = [10, 20, 30, 60, 120];

          if(!acceptedValues.includes(time)){
            this._returnMessage(`Não há essa opção de ${time} minutos. As opções são 10,20, 30, 1 hora e 2 horas.`);
          }

          console.log("Valor extraído da sentença:");
          console.log(time);
          this.sendRequest(`${command.action}-${time}`);
        } else if(command.commandClass == 'stopApplication'){
          this._returnMessage('Comando recebido. Vou parar de escutar agora mesmo.');
          await this.endSpeech();
          stopListening = true;
        }
      } else {
        this.sendRequest(command.action);
      }
    }


    if(!stopListening){
      await this.endSpeech();
  
      setTimeout(this.startSpeech(), 500);
    }

  }

  onSpeechStartHandler() {
    console.log('startou');
    this.setState({
      isListening: true,
      textButton: 'PARAR'
    });
  }

  render() {
    console.log(this.state.text);

    let br = "\n\n\n";

    return (
      <View style={styles.container}>
        <Text style={styles.welcome}>Bem-vindo ao Speech Recognition!</Text>
       
        <Button
          onPress={startSpeech}
          title={this.state.textButton}
          color="#841584"
          accessibilityLabel="start speech"
          />

          <Text>{br}</Text>

          <Text>{this.state.text}</Text>
        
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  welcome: {
    fontSize: 20,
    textAlign: 'center',
    margin: 10,
  },
  instructions: {
    textAlign: 'center',
    color: '#333333',
    marginBottom: 5,
  },
});
