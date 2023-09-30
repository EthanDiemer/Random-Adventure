#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

// game variables
int defeated = 0;
int input;
int drop;
int heal;
int healthPots = 5;
int roundNumber = 1;
//
// hero variables
int heroHealth = 30;
int heroAttack;
int heroMana = 100;
int weapon = 0;
//
// monster variables
int monsterMaxHealth;
int monsterHealth;
int monsterAttack;
int monsterType;
//

void green(){printf("\033[0;32m");}
void yellow(){printf("\033[0;33m");}
void red(){printf("\033[0;31m");}
void white(){printf("\033[0;37m");}
void printStart();

void printHealth(int currentHealth, int hero){
  if(hero==0){
    if(currentHealth >= (30 * 2) / 3){//green
      green();
      printf("%d",currentHealth);
      white();
    }
    if(currentHealth > (30) / 3 && currentHealth < (30 * 2) / 3){
      yellow();
      printf("%d\t\t",currentHealth);
      white();
    }
    if(currentHealth <= (30) / 3){//red
      red();
      printf("%d\t\t",currentHealth);
      white();
    }
  }
  else{
    if(currentHealth >= (monsterMaxHealth * 2) / 3){//green
      green();
      printf("%d\n",currentHealth);
      white();
    }
    if(currentHealth > (monsterMaxHealth) / 3 && currentHealth < (monsterMaxHealth * 2) / 3){
      yellow();
      printf("%d\n",currentHealth);
      white();
    }
    if(currentHealth <= (monsterMaxHealth) / 3){//red
      red();
      printf("%d\n",currentHealth);
      white();
    }
  }
}

void printInformation(){
  system("clear");
  puts("-------");
  puts("Enemies");
  puts("-------\n");
  puts("Zombie:\n\tHealth: 10\n\tDamage: 0 - 9\n");
  puts("Goblin:\n\tHealth: 15\n\tDamage: 0 - 12\n");
  puts("Wolf:\n\tHealth: 20\n\tDamage: 0 - 10\n");
  puts("Orc:\n\tHealth: 25\n\tDamage: 0 - 13\n");
  puts("Golem:\n\tHealth: 40\n\tDamage: 1 - 11\n");
  puts("----");
  puts("Hero");
  puts("----\n");
  puts("Starting Health: 30");
  puts("Starting Health Pots: 5\n\tHealth Pots Heal: 7 - 14");
  puts("Starting Mana: 100\n");
  puts("-------");
  puts("Weapons");
  puts("-------\n");
  puts("Fists (starting weapon): 0 - 13 damage");
  puts("Dagger: 0 - 14 damage");
  puts("Sword: 0 - 16 damage");
  puts("Axe: 0 - 17 damage");
  puts("Great Sword: 0 - 21 damage\n");
  puts("-----");
  puts("Magic");
  puts("-----\n");
  puts("Heal:\n\tHeals: 7 - 14\n\tCosts: 20");
  puts("Fire:\n\tDamage: 5 - 10\n\tCosts: 10");
  puts("Lightning:\n\tDamage: 7 - 14\nCosts: 15\n");
  puts("Enter Any Number to Continue");
  scanf("%d",&input);
  printStart();
}
void printStart(){
  system("clear"); 
  puts("----------------");
  puts("Random Adventure");
  puts("----------------\n");
  puts("Start Game - 1\nInformation - 2");
  scanf("%d",&input);
  if(input==2){printInformation();}
}
//print health function hero and monster
void printRoundStart(){
  puts("--------");
  printf("Round %d\n",roundNumber);
  puts("--------");
  //printf("Hero Health: %d\t\tMonster Health: %d\n",heroHealth,monsterHealth);
  ///*
  printf("Hero Health: ");
  printHealth(heroHealth,0);
  printf("        Monster Health: ");
  printHealth(monsterHealth,2);
  //*/
  printf("Hero Mana: %d\n\n",heroMana);
  
}
void Rounds(){
  system("clear");  
  printRoundStart();
  printf("1 - Attack\n2 - Heal\n3 - Magic\n");
  scanf("%d",&input);
  system("clear");
  printRoundStart();
}

void HeroAttack(){
  //varaible for the hero attack damage
  srand(time(0));
  int attack;
  if (input==2){attack = rand()%6 + 5;}//fire
  else if (input==3){attack = rand()%8 + 7;}//lightning
  else{
    switch(weapon){
      case 0:
        attack = rand()%8; //fist
      break;
      case 1:
        attack = rand()%9; //dagger
      break;
      case 2:
        attack = rand()%11; //sword
      break;
      case 3:
        attack = rand()%12; //axe
      break;
      case 4:
        attack = rand()%16;; //great sword
      break;
    }
    if(rand()%10 == 0 && attack>1){
      puts("Critical Hit");
      attack += 6;
    }
  }
  heroAttack = attack;
  printf("Hero attacks with %d damage    ",heroAttack);
  monsterHealth -= heroAttack;
  printf("  Monsters health is ");
  printHealth(monsterHealth,1);
}

void HeroHeal(){
  srand(time(0));
  heal = rand()%8+7;
  if(heal + heroHealth > 30){
    heal = 30 - heroHealth;
    heroHealth = 30;
  }
  else{
    heroHealth += heal;
  }
  printf("Hero heals for %d health.       Hero Health is ",heal);
  printHealth(heroHealth,0);
  puts("");
  if(input==2){
    healthPots--;
    printf("%d health pots left\n",healthPots);
  }
}

void HeroMagic(){
  srand(time(0));
  puts("What magic would you like to use");
  puts("1 - Heal\n2 - Fire\n3 - Lightning\n4 - Back");
  scanf("%d",&input);
  switch(input){
    case 1:
      if(heroMana<20){
        puts("Not enough mana for this spell");
        HeroMagic();
      }
      else{
        heroMana -= 20;
        HeroHeal();
        printf("Current Mana is %d\n",heroMana);
      }
    break;
    case 2:
      if(heroMana<5){
        puts("Not enough mana for this spell");
        HeroMagic();
      }
      else{
        heroMana -= 10;
        HeroAttack();
        printf("Current Mana is %d\n",heroMana);
      }
    break;
    case 3:
      if(heroMana<15){
        puts("Not enough mana for this spell");
        HeroMagic();
      }
      else{
        heroMana -= 15;
        HeroAttack();
        printf("Current Mana is %d\n",heroMana);
      }
    break;
    case 4:
      system("clear");
    break;
    default:
      puts("Invalid input");
      HeroMagic();
    break;
  }
}

void MonsterAttacks(){
  //variable for the attack damage
  srand(time(0));
  int attack; 
  switch(monsterType){
    case 1:
      attack = rand()%6;//zombie
      break;
    case 2:
      attack = rand()%9;//goblin
      break;
    case 3:
      attack = rand()%7;//wolf
      break;
    case 4:
      attack = rand()%10;//orc
    break;
    case 5:
      attack = rand()%7 + 1;//golem
    break;
  }
  if(rand()%15 == 0 && attack>1){
    puts("Critical Hit");
    attack += 4;
  }
  monsterAttack = attack;
  heroHealth -= monsterAttack;
  printf("Monster attacks with %d damage ",monsterAttack);
  printf("  Hero health is ");
  printHealth(heroHealth,0);
  puts("");
}

void MonsterDrop(){
  srand(time(0));
  int item;
  int drop = rand()%75+1;
  if(drop<=25){
    item = rand()%2+1;
    printf("\nThe monster dropped %d health pots\n", item);
    healthPots += item;
    sleep(1);
  }
  else if (drop>25 && drop<=50){
    item = rand()%4;
    switch(item){
      case 0: //dagger
        puts("\nThe monster droped a dagger");
        puts("Do you want the weapon");
        puts("1 - Yes\n2 - No");
        scanf("%d",&input);
        if (input==1){weapon=1;}
      break;
      case 1: //sword
        puts("\nThe monster droped a sword");
        puts("Do you want the weapon");
        puts("1 - Yes\n2 - No");
        scanf("%d",&input);
        if (input==1){weapon=2;}
      break;
      case 2: //axe
        puts("\nThe monster droped an axe");
        puts("Do you want the weapon");
        puts("1 - Yes\n2 - No");
        scanf("%d",&input);
        if (input==1){weapon=3;}
      break;
      case 3: //great sword
        puts("\nThe monster droped a great sword");
        puts("Do you want the weapon");
        puts("1 - Yes\n2 - No");
        scanf("%d",&input);
        if (input==1){weapon=4;}
      break;
    }
  }
}

int main(void) {
  system("clear");
  srand(time(0));  
  printStart();
  system("clear");
  while(heroHealth>0){
    //deciding the type of monster
    monsterType = rand()%5 + 1;
    switch(monsterType){
      case 1:
        monsterHealth = 10; //zombie
        monsterMaxHealth = monsterHealth;
        puts("A zombie has appeared!");
      break;
      case 2:
        monsterHealth = 15; //goblin
        monsterMaxHealth = monsterHealth;
        puts("A goblin has appeared!");
      break;
      case 3:
        monsterHealth = 20; //wolf
        monsterMaxHealth = monsterHealth;
        puts("A wolf has appeared!");
      break;
      case 4:
        monsterHealth = 25; //orc
        monsterMaxHealth = monsterHealth;
        puts("An orc has appeared!");
      break;
      case 5:
        monsterHealth = 40; //golem
        monsterMaxHealth = monsterHealth;
        puts("A golem has appeared!");
      break;
    }    
    sleep(2);
    system("clear");
    //
    while(monsterHealth>0 && heroHealth>0){
      Rounds();
      switch(input){
        case 1:
          HeroAttack();          
        break;
        case 2:
          if(healthPots==0){
            puts("Not enough health pots");
            sleep(1);
            continue;
          }
          HeroHeal();
        break;
        case 3:
          if(heroMana<10){
            puts("Not enough mana for any spells");
            sleep(1);
            continue;
          }
          HeroMagic();
          if(input==4){continue;}
        break;
        default:
          puts("Invalid input");
          sleep(1);
          continue;
        break;
      }      
      if(monsterHealth<=0){
        switch(monsterType){
          case 1:
            puts("Zombie Defeated");
          break;
          case 2:
            puts("Goblin Defeated");
          break;
          case 3:
            puts("Wolf Defeated");
          break;
          case 4:
            puts("Orc Defeated");
          break;
          case 5:
            puts("Golem Defeated");
          break;
        }
        defeated++;
        roundNumber++;
        sleep(2);
        MonsterDrop();
        continue;
      }
      sleep(1);
      // monster attack
      MonsterAttacks();
      if(heroHealth<=0){sleep(1);continue;}
      roundNumber++;
      if(heroMana<100){heroMana+=5;}
      sleep(2);
      system("clear");
    }
    system("clear");
  }

  puts("You Died");
  printf("Rounds lasted: %d\n",roundNumber);
  printf("Monsters defeated: %d\n",defeated);
}