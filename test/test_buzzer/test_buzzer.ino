//définition des fréquences des notes de musique de la 4eme octave
#define OCTAVE_4_DO 523
#define OCTAVE_4_RE 587
#define OCTAVE_4_MI 659
#define OCTAVE_4_FA 698
#define OCTAVE_4_SOL 784
#define OCTAVE_4_LA 880
#define OCTAVE_4_SI 988

//définition de la durée d'un temps
#define DUREE_TEMPS 300
#define SILENCE 70

void setup() {
  
}

void loop() {
 JouerMusique();
}

void JouerNote(unsigned int note, unsigned int nombreDeTemps){
  tone(2, note, nombreDeTemps * DUREE_TEMPS);
  delay(nombreDeTemps * DUREE_TEMPS);
  delay(SILENCE);
}

void JouerMusique(){
   //Jouer les 11 première notes
  JouerNote(OCTAVE_4_DO, 1);
  JouerNote(OCTAVE_4_DO, 1);
  JouerNote(OCTAVE_4_DO, 1);
  JouerNote(OCTAVE_4_RE, 1);
  JouerNote(OCTAVE_4_MI, 2);
  JouerNote(OCTAVE_4_RE, 2);
  JouerNote(OCTAVE_4_DO, 1);
  JouerNote(OCTAVE_4_MI, 1);
  JouerNote(OCTAVE_4_RE, 1);
  JouerNote(OCTAVE_4_RE, 1);
  JouerNote(OCTAVE_4_DO, 4);
  //delai avant de rejouer le début de la mélodie
  delay(1500);
}
