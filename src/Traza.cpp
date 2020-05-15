#include "Traza.h"

void Traza::mensaje(char *str, ...)
{
  int count=0;  
  String cad="";
  
  for(int i=0; str[i]!='\0';i++)  if(str[i]=='%')  count++; //Evaluate number of arguments required to be printed
  
  va_list argv;
  va_start(argv, count);
  
  for(int i=0; str[i]!='\0';i++) //Iterate over formatting string
    {
    if(str[i]=='%')
      {    
      boolean flag=true;  
      while(flag)
        {
        flag=false;
        switch(str[++i])
          {
          case 'i':
          case 'd': 
            cad += String(va_arg(argv, int));
            break;
          case 'l': 
            cad += String(va_arg(argv, long));
            break;
          case 'f': 
            cad += String(va_arg(argv, double));
            break;
          case 'c': 
            cad += String((char)va_arg(argv, int));
            break;
          case 's':
            cad += String(va_arg(argv, char *));
            break;
          default: 
            flag=true;//para saltar los argumentos entre el % y la letra 
          }
        }
      }
    else cad += String(str[i]);
  }

  switch (_medio)
    {
    case serie:
      Serial.print(cad); 
      //break;
    case ethernet:
      escribeTCP(cad);
      break;
    case fichero:
      break;
    default:
      break;
    }
}

void Traza::escribeTCP(String mensaje)
  {
  if(!_cliente.connected()) _cliente = _servidor.available(); 
  
  if (_cliente) _cliente.print(mensaje.c_str());  //"Hola mundo...\n");
  else Serial.println(".");
  }

void Traza::begin(uint8_t nivel=MAX_NIVELDEBUG, medios_t medio=serie)
  {
  _nivelDebug=nivel;
  _medio=medio;

  _servidor.begin();
  }

/*
int Traza::printf(char *str, ...)
{
  int i, count=0, j=0;
  char temp[BUFFER+1];

  for(i=0; str[i]!='\0';i++)  if(str[i]=='%')  count++; //Evaluate number of arguments required to be printed
  
  va_list argv;
  va_start(argv, count);
  for(i=0,j=0; str[i]!='\0';i++) //Iterate over formatting string
  {
    if(str[i]=='%')
    {
      //Clear buffer
      temp[j] = '\0'; 
      Serial.print(temp);
      j=0;
      temp[0] = '\0';
      
      //Process argument
      switch(str[++i])
      {
        case 'i':
        case 'd': Serial.print(va_arg(argv, int));
                  break;
        case 'l': Serial.print(va_arg(argv, long));
                  break;
        case 'f': Serial.print(va_arg(argv, double));
                  break;
        case 'c': Serial.print((char)va_arg(argv, int));
                  break;
        case 's': Serial.print(va_arg(argv, char *));
                  break;
        default:  ;
      }
    }
    else 
    {
      //Add to buffer
      temp[j] = str[i];
      j = (j+1)%BUFFER;
      if(j==0)  //If buffer is full, empty buffer.
      {
        temp[BUFFER] = '\0';
        Serial.print(temp);
        temp[0]='\0';
      }
    }
  }

  temp[j] = '\0';
  Serial.println(temp); //Print trailing newline
  return count + 1; //Return number of arguments detected
}
*/  
