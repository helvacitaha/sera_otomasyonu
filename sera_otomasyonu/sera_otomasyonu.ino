#include <Servo.h> // Servo motorlarımızı kullanmak için kütüphanesini kodumuza dahil ettik.
Servo su_servosu; // Motorumuzu belirledik.
Servo hava_kapisi_servosu; // Motorumuzu belirledik.
#define su_servosu_pin 2 // Su boşaltım servosunu bağladığımız dijital pini belirledik.
#define hava_kapisi_servosu_pin 3 // Hava kapısını açıp kapadığımız dijital pini belirledik.
#define isiklar 4 // Işıklarımızı bağladığımız dijital pini belirledik.
#define sicaklik_sensoru A0 // Sıcaklık sensörümüzü bağladığımız analog pini belirledik.
#define sicaklik_uyari_lambasi 13 // Sıcaklık uyarı lambasını bağladığımız dijital pini belirledik.
#define toprak_nem_sensoru 5 // Toprak nem sensörünü bağladığımız dijital pini belirledik.
#define isik_sensoru A1 // Işık sensörümüzü bağladığımız analog pini belirledik.
#define gaz_sensoru 6 // Zehirli gaz sensörümüzü bağladığımız dijital pini belirledik.
#define zehirli_gaz_uyari_dudugu // Zehirli gaz uyarı düdüğümüzü bağladığımız dijital pini belirledik.

#define BITKI_MAKSIMUM_SICAKLIK 28.2 // Bitkinin bulunabileceği en yüksek sıcaklığı belirledik
#define BITKI_MINIMUM_SICAKLIK 17.6 // Bitkinin bulunabileceği en düşük sıcaklığı belirledik

void setup() {
  
  su_servosu.attach(su_servosu_pin); // Su servosu için belirlediğimiz pini belirlenen pine bağladık.
  hava_kapisi_servosu.attach(hava_kapisi_servosu_pin); // Hava kapısı servosu için belirlediğimiz pini belirlenen pine bağladık.
  su_servosu.write(0); // Su servomuzu başlangıç konumuna getirdik.
  hava_kapisi_servosu.write(0); // Hava kapısı servomuzu başlangıç konumuna getirdik.
  pinMode(isiklar,OUTPUT); // Işıklarımızı bağladığımız dijital pini çıkış pini olarak ayarladık.
  pinMode(sicaklik_sensoru,INPUT); // Sıcaklık sensörümüzü bağladığımız analog pini giriş pini olarak ayarladık.
  pinMode(sicaklik_uyari_lambasi,OUTPUT); // Sıcaklık uyarı lambamızı bağladığımız dijital pini çıkış pini olarak ayarladık.
  pinMode(toprak_nem_sensoru,INPUT); // Toprak nem sensörümüzü bağladığımız dijital pini giriş pini olarak ayarladık.
  pinMode(isik_sensoru,INPUT); // Işık sensörümüzü bağladığımız analog pini giriş pini olarak ayarladık.
  pinMode(gaz_sensoru,INPUT); // Gaz sensörümüzü bağladığımız dijital pini giriş pini olarak ayarladık.
  pinMode(zehirli_gaz_uyari_dudugu,OUTPUT); // Zehirli gaz uyarı düdüğümüzü bağladığımız dijital pini çıkış pini olarak ayarladık.

}

void loop() {

    float sicaklik=(analogRead(sicalik_sensoru)*1023)/500; // Sıcaklığı Celsius cinsinden bulmak için "analogRead" komutuyla aldığımız 0-1023 arasındaki değeri
                                                           // matematiksel işlemlerle Celsius birimine dönüştürdük.
                                                           
    if(sicaklik>BITKI_MAKSIMUM_SICAKLIK||sicaklik<BITKI_MINIMUM_SICAKLIK){ // Sıcaklık BITKI_MAKSIMUM_SICAKLIK değerinden fazla veya BITKI_MINIMUM_SICAKLIK değerinden düşükse:

          digitalWrite(sicaklik_uyari_lambasi,1); // Sıcaklık uyarı lambamızı açık duruma getirdik.
      
      }
      
      else{ // Yukarıdaki koşul sağlanmıyorsa (değilse):
        
           digitalWrite(sicaklik_uyari_lambasi,0); // Sıcaklık uyarı lambamızı kapalı konuma getirdik.
        
        }

    bool toprak_nem_sensoru_verisi=digitalRead(toprak_nem_sensoru); // Toprak nem sensöründen gelen bilgiyi "bool" türünden değişkenin içerisine atadık.

    if(toprak_nem_sensoru_verisi){ // Toprak nem sensöründen eşik değerin üstünde değer geliyorsa(ıslaksa):
      
          su_servosu.write(75); // Su servomuzu 75 derece konumuna getiriyoruz.
      
      }
      
      else{ // Yukarıdaki koşul sağlanmıyorsa (değilse):
        
          su_servosu.write(0); // Su servomuzu 0 derece konumuna getiriyoruz.
        
        }

    int isik_degeri=analogRead(isik_sensoru); // Işık sensöründen gelen bilgiyi "int" türünden bir değişkene atadık.
    isik_degeri=map(isik_sensoru,0,1023,100,0); // Sensör verisini 0-1023 aralığından 0-100 aralığına daralttık.

    if(isik_degeri>70){ // Işık değeri %70'ten fazlaysa (aydınlıksa):
     
        digitalWrite(isiklar,0); // Işıkları kapat
          
    }
    else{ // Yukarıdaki koşul sağlanmıyorsa (değilse):
      
        digitalWrite(isiklar,1); // Işıkları aç.  
      
    }

    bool gaz_sensoru_veri=digitalRead(gaz_sensoru)?0:1; // Zehirli gaz sensöründen gelen bilginin tersini "bool" türünden değişkenin içerisine atadık.
                                                        // Bunun sebebi sensörden gelen bilginin ters olması. Bu bilgiyi tekrar terse çevirerek doğru bilgiyi elde ettik.

    if(gaz_sensoru_veri){ // Eğer gaz sensöründen veri geliyorsa:
      
          digitalWrite(zehirli_gaz_uyari_dudugu,1); // Zehirli gaz uyarı düdüğümüzü açıyoruz.
          hava_kapisi_servosu.write(35); // Hava kapısı servomuzu 35 derece konumuna getiriyoruz.
      
      }

    else{
        
        digitalWrite(zehirli_gaz_uyari_dudugu,0);// Zehirli gaz uyarı düdüğümüzü kapatıyoruz.
        hava_kapisi_servosu.write(0); // Hava kapısı servomuzu 0 derece konumuna getiriyoruz.
      
      }
  
}
