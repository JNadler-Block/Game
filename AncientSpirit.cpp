#include "AncientSpirit.h"
#include "Random.h"

using namespace std;

void AncientSpirit::AncientUsed(Character &c, int x) {
	Random ran;
	int r;
	int min = 0;
	int max = 0;
	int health = 0;
	int potion = 0;
	for (int i = 0; i < x; i++) {
		r = ran.RandomInt(1, 18, c.rng);
		if (r == 1 || r == 2 || r == 3 || r == 4) {
			r = ran.RandomInt(1, 10, c.rng);
			if (r == 10) {
				max += 2;
				/*c.IncreaseMaxDamage(2);
				cout << "\nYou have gained 2 maximum damage!" << endl;
				cout << "Your new damage range is ";
				cout << c.SeeMinDamage() << "-" << c.SeeMaxDamage() << endl;*/
			}
			else {
				max++;
				/*c.IncreaseMaxDamage();
				cout << "\nYou have gained 1 maximum damage!" << endl;
				cout << "Your new damage range is ";
				cout << c.SeeMinDamage() << "-" << c.SeeMaxDamage() << endl;*/
			}
		}
		else if (r == 5 || r == 6) {
			if (c.SeeMinDamage() == c.SeeMaxDamage()) {
				max++;
				/*c.IncreaseMaxDamage();
				cout << "\nYou have gained 1 maximum damage!" << endl;
				cout << "Your new damage range is ";
				cout << c.SeeMinDamage() << "-" << c.SeeMaxDamage() << endl;*/
			}
			else {
				r = ran.RandomInt(1, 10, c.rng);
				if (r == 10 && c.SeeMinDamage() < (c.SeeMaxDamage() - 1)) {
					min += 2;
					/*c.IncreaseMinDamage(2);
					cout << "\nYou have gained 2 minimum damage!" << endl;
					cout << "Your new damage range is ";
					cout << c.SeeMinDamage() << "-" << c.SeeMaxDamage() << endl;*/
				}
				else {
					min++;
					/*c.IncreaseMinDamage();
					cout << "\nYou have gained 1 minimum damage!" << endl;
					cout << "Your new damage range is ";
					cout << c.SeeMinDamage() << "-" << c.SeeMaxDamage() << endl;*/
				}
			}
		}
		else {
			health += 5;
			//c.IncreaseHealth(5);
			//cout << "\nYou have gained 5 maximum health!" << endl;
			//cout << "Your maximum health is now " << c.SeeHealth() << endl;
			if ((c.SeeHealth() + health) % 100 == 0) {
				//cout << "Potions now heal you for 5 more health!" << endl;
				potion += 5;
			}
		}
		c.DecreaseAncientCount();
	}
	cout << endl;
	c.IncreaseMaxDamage(max);
	c.IncreaseMinDamage(min);
	if (health > 0) {
		cout << "You have gained " << health << " maximum health!" << endl;
		c.IncreaseHealth(health);
	}
	if (max > 0 && min > 0 && (max > min)) {
		cout << "You have gained " << min << "-" << max << " damage!" << endl;
	}
	else if (max > 0 && min > 0) {
		cout << "You have gained " << min << " minimum damage!" << endl;
		cout << "You have gained " << max << " maximum damage!" << endl;
	}
	else if (min > 0) {
		cout << "You have gained " << min << " minimum damage!" << endl;
	}
	else if (max > 0) {
		cout << "You have gained " << max << " maximum damage!" << endl;
	}
	if (potion > 0) {
		cout << "Potions now heal you for " << potion << " more health!" << endl;
	}
	if (max > 0 || min > 0) {
		cout << "Your new damage range is ";
		cout << c.SeeMinDamage() << "-" << c.SeeMaxDamage() << endl;
	}
	cout << "Your currently have " << c.SeeCurrentHealth() << " out of " << c.SeeHealth() << " health." << endl;
}

void AncientSpirit::EternalUsed(Character& c, int x) {
	/*Random ran;
	int r = ran.RandomInt(1, 25, c.rng);
	if (r == 25) {
		c.IncreaseDamageReduction(5);
		c.DecreaseEternalCount();
		//cout << "\nYou have gained 5 damage reduction!!!" << endl;
		//cout << "You now have " << c.SeeDamageReduction() << " damage reduction." << endl;
	}
	else {
		c.IncreaseDamageReduction();
		c.DecreaseEternalCount();
		//cout << "\nYou have gained 1 damage reduction!" << endl;
		//cout << "You now have " << c.SeeDamageReduction() << " damage reduction." << endl;
	}*/
	cout << setprecision(2) << fixed;
	if (c.SeeDR() == 0) {
		cout << "\nYou have gone from 0% to ";
	}
	else {
		cout << "\nYou have gone from " << 100 * c.SeeDR() << "% to ";
	}
	for (int i = 0; i < x; i++) {
		c.IncreaseDamageReduction();
		c.DecreaseEternalCount();
	}
	c.DamageReductionCalculator();
	cout << 100 * c.SeeDR() << "% damage reduction" << endl;
}
