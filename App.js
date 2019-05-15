/**
 * Sample React Native App
 * https://github.com/facebook/react-native
 *
 * @format
 * @flow
 */

import React, {Component} from 'react';
import {Platform, StyleSheet, Text, View} from 'react-native';
import Voice from 'react-native-voice';
import { Button } from 'react-native';
import { PermissionsAndroid } from 'react-native';


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
      api_url: 'http://192.168.43.221:8081/commands/' 
    }; 
  }

  async componentDidMount() {
    await this.requestVoiceRecord();
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
  }

  sendRequest(url) {
    fetch(`http://192.168.43.221:8082/${url}`, 
      {method: 'GET', headers: {}, mode: 'cors', cache: 'default'}
      )
        .then( (res) => {
          alert(`Enviou ${url}!`);
          console.log('Response:');
          console.log(res);
        });
  }

  onSpeechResultsHandler(e) {
    console.log('resultados:');
    console.log(e);
    
    let text = e.value[0];

    this.setState({
      text
    });

    switch(text.toLowerCase()) {
      case 'ligar': this.sendRequest('ligar'); break;
      case 'desligar': this.sendRequest('desligar'); break;
      case 'aumentar volume': this.sendRequest('aumentarvolume'); break;
      case 'band': this.sendRequest('band'); break;
      case 'globo': this.sendRequest('globo'); break;
    }
  }

  onSpeechStartHandler() {
    console.log('startou');
  }

  render() {
    console.log(this.state.text);

    let br = "\n\n\n";

    return (
      <View style={styles.container}>
        <Text style={styles.welcome}>Bem-vindo ao Speech Recognition!</Text>
       
        <Button
          onPress={startSpeech}
          title="FALAR"
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
