#include <ESP8266WiFi.h>//Biblioteca que gerencia o WiFi.
#include <WiFiServer.h>//Biblioteca que gerencia o uso do TCP.
 
WiFiServer servidor(80);//Cria um objeto "servidor" na porta 80 (http).
WiFiClient cliente;//Cria um objeto "cliente".
 
String html;

void setup()
{
   Serial.begin(115200);//Inicia comunicaçao Serial.
 
   WiFi.mode(WIFI_STA);//Habilita o modo STATION.
   WiFi.begin("GVT-88D5", "9507454979");//Conecta no WiFi (COLOQUE O NOME E SENHA DA SUA REDE!).
 
   Serial.println(WiFi.localIP());//Printa o IP que foi consebido ao ESP8266 (este ip que voce ira acessar).
   servidor.begin();//Inicia o Servidor.
 
   pinMode(D4, OUTPUT);//Define o LED_BUILTIN como Saida.
}
 
void loop()
{   
   http();//Sub rotina para verificaçao de clientes conectados.
}
 
void http()//Sub rotina que verifica novos clientes e se sim, envia o HTML.
{
   cliente = servidor.available();//Diz ao cliente que há um servidor disponivel.
   
   if (cliente == true)//Se houver clientes conectados, ira enviar o HTML.
   {
      String req = cliente.readStringUntil('\r');//Faz a leitura do Cliente.
      Serial.println(req);//Printa o pedido no Serial monitor.    
/*
      html = "";//Reseta a string.
      html += "HTTP/1.1 Content-Type: text/html\n\n";//Identificaçao do HTML.
      html += "<!DOCTYPE html><html><head><title>ESP8266 WEB</title>";//Identificaçao e Titulo.
      html += "<meta name='viewport' content='user-scalable=no'>";//Desabilita o Zoom.
      html += "<style>h1{font-size:2vw;color:black;}</style></head>";//Cria uma nova fonte de tamanho e cor X.
      html += "<body bgcolor='ffffff'><center><h1>";//Cor do Background
 
      //Estas linhas acima sao parte essencial do codigo, só altere se souber o que esta fazendo!
 
      html += "<form action='/LED' method='get'>";//Cria um botao GET para o link /LED
      html += "<input type='submit' value='LED' id='frm1_submit'/></form>";
 
      html += "</h1></center></body></html>";//Termino e fechamento de TAG`s do HTML. Nao altere nada sem saber!
*/
      float tensaoRandom = random(110, 130);
      float correnteRandom = random(5, 10);
      float potenciaRandom = random(600, 800);
      float fpRandom = random(1, 5);

      html = "<!DOCTYPE html><html lang='pt-br'><head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1.0'><meta http-equiv='X-UA-Compatible' content='ie=edge'><title>Interface Gráfica</title><link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css'><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js'></script><script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js'></script><script src='https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js'></script><script src='https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js'></script><script src='https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js'></script><style>.col-sm-8{margin-bottom: 50px;}.text{color: #8E8E8E;font: normal 13pt Segoe UI;text-align: right;}.info{color: #605D5D;font: normal 30pt Segoe UI;text-align: left;}.container{margin-top: 30px;position: relative;}</style></head><body onload='mudarValor()'><div class='container mt-3'><div class='row'><div class='col-sm-3'><button type='button' class='btn btn-primary' data-toggle='modal'data-target='#myModal'>Abrir configurações</button></div></div></div><div class='modal fade' id='myModal'><div class='modal-dialog'><div class='modal-content'><div class='modal-header'><h4 class='modal-title'>Configurações</h4><button type='button' class='close' data-dismiss='modal'>x</button></div><div class='modal-body'><h7>Nome</h7></br><h5>IFES Campus Guarapari</h5></br></br></div><div class='modal-body'><h7>Dispositivo</h7></br><h5>Microondas</h5><h7>Tomada</h7></br><h5>127 V</h5></br></br></div><div class='modal-footer'><button type='button' class='btn btn-danger' data-dismiss='modal'>Fechar</button></div></div></div></div><div class='container'><div class='row'><div class='col-sm-2'></div><div class='col-sm-8'><canvas id = 'myChart' width='100' height='50'></canvas></div></div></div><div class='container'><div class='row'><div class='col-sm-2'><p class='text'>Tensão</p></br></div><div class='col-sm-4'><p class='info' id='tensao'></p></div><div class='col-sm-2'><p class='text'>Potência</p></br></div><div class='col-sm-4'><p class='info' id='potencia'></p></div></div></div><div class='container'><div class='row'><div class='col-sm-2'><p class='text'>Corrente</p></br></div><div class='col-sm-4'><p class='info' id='corrente'></p></div><div class='col-sm-2'><p class='text'>Fator de Potência</p></br></div><div class='col-sm-4'><p class='info' id='fp'></p></div></div></div><script src='https://cdn.jsdelivr.net/npm/chart.js@2.8.0'></script><script>var ctx = document.getElementById('myChart').getContext('2d');var myChart = new Chart(ctx, {type: 'line',data: {datasets: [{label: 'Gráfico de Consumo',backgroundColor: 'rgb(255, 133, 152, 0.2)',pointBorderColor: 'rgb(255, 133, 152)',borderColor: 'rgb(255, 133, 152)',data: [1000, 1432, 2256, 2574, 3713]}], labels: ['29/Jan', '30/Jan', '31/Jan', '01/Fev', '02/Fev']},options: {}});</script><script>";
      html += "function mudarValor(){";
      html += "setInternal(function(){";
      html += "document.getElementById('tensao').innerText = ";
      html += "Math.random()";
      html += ";";
      html += "document.getElementById('corrente').innerText = ";
      html += correnteRandom;
      html += ";";
      html += "document.getElementById('potencia').innerText = ";
      html += potenciaRandom;
      html += ";";
      html += "document.getElementById('fp').innerText = ";
      html += fpRandom;
      html += ";";
      html += "}, 5000)}";
      html += "</script></body></html>";
      
      cliente.print(html);//Finalmente, enviamos o HTML para o cliente.      
      cliente.stop();//Encerra a conexao.
      
   }else{
      Serial.println("");
      Serial.println(WiFi.localIP());
   }
}
 
