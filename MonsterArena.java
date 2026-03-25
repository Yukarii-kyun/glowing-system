import java.util.Scanner;
import java.util.Random;


public class MonsterArena {
    
    public Random rand = new Random();
    public Scanner scan = new Scanner(System.in);

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
        String heroName = scanner.nextLine().trim();
        if (heroName.isEmpty()) heroName = "Hero";
}
