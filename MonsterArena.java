import java.util.Scanner;
import java.util.Random;


public class MonsterArena {
    
    public static Random rand = new Random();
    public static Scanner scan = new Scanner(System.in);

    //Chracter
    static class Character {
        String name;
        int health, maxHealth,attack, defense;
        boolean isDefending = false;

        Character(String name, int health, int attack, int defense) {
            this.name = name;
            this.health = health;
            this.maxHealth = health;
            this.attack = attack;
            this.defense = defense;
        }

        Boolean isAlive() {
            return health > 0;
        }
        //Returns the actual damage taken after defense is applied, and resets defending status
        int takeDamage(int raw) {
            int def = isDefending ? defense * 2 : defense;
            int damage = Math.max(1, raw - def); // Ensure at least 1 damage is taken
            health = Math.max(0, health - damage);
            isDefending = false; // Reset defending status after taking damage
            return damage;
        }

        //Rolls an attack value with some random variance based on the character's attack stat
        int rollAttack() {
            int variance = (int)(attack * 0.2);
            return attack + rand.nextInt(variance * 2 + 1) - variance;
        }

        void heal(int amount) {
            health = Math.min(maxHealth, health + amount);
        }

        String healthbar() {
            int filled = (int)((double)health / maxHealth * 20);
            return "[" + "=".repeat(filled) + " ".repeat(20 - filled) + "] " + health + "/" + maxHealth;
        }
    }

     public static void main(String[] args) {
        System.out.println("╔══════════════════════════════╗");
        System.out.println("║     TURN-BASED BATTLE RPG    ║");
        System.out.println("╚══════════════════════════════╝\n");
 
        System.out.print("Enter your hero's name: ");
        String heroName = scan.nextLine().trim();
        if (heroName.isEmpty()) heroName = "Hero";

        Character hero = new Character(heroName, 100, 20, 5);
        Character monster = new Character("Dark Goblin", 80, 15, 3);

        System.out.println("\nA wild " + monster.name + " appears!");

        int turn = 1;

        // Main game loop
        while (hero.isAlive() && monster.isAlive()) {
            System.out.println("\n--- Turn " + turn + " ---");
            System.out.println(hero.name + ": " + hero.healthbar());
            System.out.println(mosnter.name + ": " + mosnter.healthbar());

            // Player's turn
           int action = playerMenu(hero);
           System.out,println();
           

            switch (action) {
                case 1: // Attack
                    int damage = hero.rollAttack();
                    int actualDamage = monster.takeDamage(damage);
                    System.out.println(hero.name + " attacks for " + damage + " damage! (" + actualDamage + " after defense)");
                    break;
                case 2: // Defend
                    hero.isDefending = true;
                    System.out.println(hero.name + " is defending!");
                    break;
                case 3: // Heal
                    int healAmount = 20;
                    hero.heal(healAmount);
                    System.out.println(hero.name + " heals for " + healAmount + " health!");
                    break;
            }

            // Check if monster is defeated
            if (!monster.isAlive()) break;
               
            //monster's turn(simple ai)
            System.out.println();
            monsterTurn(monster, hero);

            turn++;
            System.out.println();
        }
        //Reult
        System.out.println("--- Battle Over ---");
        if (hero.isAlive()) {
            System.out.println("🏆 Victory!" + hero.name + "defeated the" + monster.name + "!");
            }else {
            System.out.println("💀 Defeat... " + hero.name + " was slain by the " + monster.name + "...");
         }
         System.out.println("Survived" + turn + "turn(s). Thanks for playing!");

         scan.close();

        }

        //Player action menu
        static int playerMenu(Character hero) {
            System.out.println("\nYour turn! What will you do?");
            System.out.println("Choose an action:");
            System.out.println("1. Attack");
            System.out.println("2. Defend");
            System.out.println("3. Heal");

            while (true) {
              String input = scan.nextLine().trim();
              if(input.equals("1") || input.equals("2") || input.equals("3")) {
                return Integer.parseInt(input);
              }
                System.out.println("Please enter 1, 2, or 3.");
        }

        //Monster AI turn
        static void monsterTurn(Character monster, Character hero) {
             //Heal if health is low, otherwise attack
            double healthRatio = (double)monster.health / monster.maxHealth;
            int roll = rand.nextInt(100);

            if(healthRatio < 0.3 && roll < 25) {
                int healAmount = 10 + rand.nextInt(6); // Heal for 10-15
                monster.heal(healAmount);
                System.out.println(monster.name + " Catches its breath and recovers " + healAmount + " health!");
            } else if(roll < 15){
                monster.isDefending = true;
                System.out.println(monster.name + " is defending!");
            } else {
                int damage = monster.rollAttack();
                int actualDamage = hero.takeDamage(damage);
                System.out.println(monster.name + " attacks for " + damage + " damage! (" + actualDamage + " after defense)");
            }
        }

        //Status display

        static void displayStatus(Character hero, Character monster) {
            System.out.println(hero.name + ": " + hero.healthbar());
            System.out.println(monster.name + ": " + monster.healthbar());
        } 

    }
}   
