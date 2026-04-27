#include "ACS_61.h"

/*
Implement all class methods here.
i.e.
string Aeroplane::get_name() {
    return this->name;
}
*/

// Aircraft methods

Aircraft::Aircraft()
{
    identifier = "";
    fuel_level = 100;
    health = 100;
    current_status = AircraftStatus::OnGround;
}
Aircraft::Aircraft(string name, int fuel, int hp, AircraftStatus status)
{
    identifier = name;
    fuel_level = (fuel < 0) ? 0 : ((fuel > 100) ? 100 : fuel);
    health = (hp < 0) ? 0 : ((hp > 100) ? 100 : hp);
    current_status = status;
    if (fuel_level == 0 && current_status == AircraftStatus::Airborne)
    {
        health = 0;
    }
    if (health == 0)
    {
        current_status = AircraftStatus::Crashed;
    }
}
Aircraft::Aircraft(const Aircraft &other)
{
    identifier = other.identifier;
    fuel_level = other.fuel_level;
    health = other.health;
    current_status = other.current_status;
    if (fuel_level == 0 && current_status == AircraftStatus::Airborne)
    {
        health = 0;
    }
    if (health == 0)
    {
        current_status = AircraftStatus::Crashed;
    }
}
void Aircraft::setIdentifier(string n)
{
    if (this->isCrashed())
    {
        return;
    }
    identifier = n;
}
void Aircraft::setHealth(int n)
{
    if (this->isCrashed())
    {
        return;
    }
    health = n;
    if (health < 0)
    {
        health = 0;
    }
    if (health > 100)
    {
        health = 100;
    }
    if (fuel_level == 0 && current_status == AircraftStatus::Airborne)
    {
        health = 0;
    }
    if (health == 0)
    {
        current_status = AircraftStatus::Crashed;
    }
}
void Aircraft::setFuelLevel(int n)
{
    if (this->isCrashed())
    {
        return;
    }
    fuel_level = n;
    if (fuel_level < 0)
    {
        fuel_level = 0;
    }
    if (fuel_level > 100)
    {
        fuel_level = 100;
    }
    if (fuel_level == 0 && current_status == AircraftStatus::Airborne)
    {
        health = 0;
    }
    if (health == 0)
    {
        current_status = AircraftStatus::Crashed;
    }
}
bool Aircraft::isCrashed()
{
    if (current_status == AircraftStatus::Crashed)
    {
        return true;
    }
    return false;
}
string Aircraft::getIdentifier() const
{
    return identifier;
}
int Aircraft::getFuelLevel() const
{
    return fuel_level;
}
int Aircraft::getFuelCapacity() const
{
    return 100;
}
int Aircraft::getHealth() const
{
    return health;
}
AircraftStatus Aircraft::getCurrentStatus() const
{
    return current_status;
}
void Aircraft::takeOff()
{
    if (this->isCrashed())
    {
        return;
    }
    if (fuel_level >= 30 && current_status == AircraftStatus::OnGround)
    {
        current_status = AircraftStatus::Airborne;
    }
}
void Aircraft::land()
{
    if (this->isCrashed())
    {
        return;
    }
    if (current_status == AircraftStatus::Airborne)
    {
        current_status = AircraftStatus::OnGround;
    }
}

// CombatAircraft methods
CombatAircraft::CombatAircraft() : Aircraft(), weapon_type(""), weapon_strength(0), weapon_count(0)
{
}
CombatAircraft::CombatAircraft(string name, int fuel, int hp, AircraftStatus status, string type, int count, int strength) : Aircraft(name, fuel, hp, status), weapon_type(type), weapon_strength(strength), weapon_count(count)
{
    if (weapon_count < 0)
    {
        weapon_count = 0;
    }
    if (weapon_strength < 0)
    {
        weapon_strength = 0;
    }
    else if (weapon_strength > 100)
    {
        weapon_strength = 100;
    }
}
CombatAircraft::CombatAircraft(const CombatAircraft &other) : Aircraft(other), weapon_count(other.weapon_count), weapon_type(other.weapon_type), weapon_strength(other.weapon_strength)
{
    if (weapon_count < 0)
    {
        weapon_count = 0;
    }
    if (weapon_strength < 0)
    {
        weapon_strength = 0;
    }
    else if (weapon_strength > 100)
    {
        weapon_strength = 100;
    }
}
void CombatAircraft::displayallinfo(ostream &os) const
{
    Aircraft::displayallinfo(os);
    os << "Weapon Type: " << weapon_type << "\nWeapon Count: " << weapon_count << "\nWeapon Strength: " << weapon_strength << endl;
}
void CombatAircraft::setWeaponType(string n)
{
    if (this->isCrashed())
    {
        return;
    }
    weapon_type = n;
}
void CombatAircraft::setWeaponStrength(int n)
{
    if (this->isCrashed())
    {
        return;
    }
    weapon_strength = n;
    if (weapon_strength < 0)
    {
        weapon_strength = 0;
    }
    else if (weapon_strength > 100)
    {
        weapon_strength = 100;
    }
}
void CombatAircraft::setWeaponCount(int n)
{
    if (this->isCrashed())
    {
        return;
    }
    weapon_count = n;
    if (weapon_count < 0)
    {
        weapon_count = 0;
    }
}
string CombatAircraft::getWeaponType() const
{
    return weapon_type;
}
int CombatAircraft::getWeaponStrength() const
{
    return weapon_strength;
}
int CombatAircraft::getWeaponCount() const
{
    return weapon_count;
}
// StealthAircraft methods
StealthAircraft::StealthAircraft() : Aircraft(), cloak_status(false)
{
}
StealthAircraft::StealthAircraft(string name, int fuel, int hp, AircraftStatus status, bool cloak) : Aircraft(name, fuel, hp, status), cloak_status(cloak)
{
    if (this->getCurrentStatus() != AircraftStatus::Airborne)
    {
        cloak_status = false;
    }
}
StealthAircraft::StealthAircraft(const StealthAircraft &other) : Aircraft(other), cloak_status(other.cloak_status)
{
    if (this->getCurrentStatus() != AircraftStatus::Airborne)
    {
        cloak_status = false;
    }
}
void StealthAircraft::displayallinfo(ostream &os) const
{
    Aircraft::displayallinfo(os);
    os << "Cloak Status: " << ((cloak_status) ? "On" : "Off") << endl;
}
bool StealthAircraft::getCloakStatus() const
{
    return cloak_status;
}
void StealthAircraft::activateCloak()
{
    if (this->isCrashed())
    {
        return;
    }
    if (this->getCurrentStatus() == AircraftStatus::Airborne)
    {
        if (this->getHealth() < 10)
        {
            this->setHealth(0);
        }
        if (this->getFuelLevel() < 15)
        {
            this->setFuelLevel(0);
        }
        if (this->getHealth() >= 10 && cloak_status == false)
        {
            this->setHealth(this->getHealth() - 10);
            if (this->getFuelLevel() >= 15)
            {
                this->setFuelLevel(this->getFuelLevel() - 15);
                if (!this->isCrashed())
                {
                    cloak_status = true;
                }
            }
        }
    }
}
void StealthAircraft::deactivateCloak()
{
    if (this->isCrashed())
    {
        return;
    }
    cloak_status = false;
}
void StealthAircraft::takeOff()
{
    if (this->isCrashed())
    {
        return;
    }
    cloak_status = false;
    Aircraft::takeOff();
}
void StealthAircraft::land()
{
    if (this->isCrashed())
    {
        return;
    }
    cloak_status = false;
    Aircraft::land();
}
// AbductorCraft methods
AbductorCraft::AbductorCraft() : Aircraft(), StealthAircraft(), abductee_count(0), abductee_capacity(0)
{
}
AbductorCraft::AbductorCraft(string name, int fuel, int hp, AircraftStatus status, bool cloak, int count, int capacity) : Aircraft(name, fuel, hp, status), StealthAircraft(name, fuel, hp, status, cloak), abductee_count(count), abductee_capacity(capacity)
{
    if (abductee_capacity < 0 && abductee_count > 0)
    {
        abductee_capacity = abductee_count;
    }
    if (abductee_capacity < 0)
    {
        abductee_capacity = 0;
    }
    if (abductee_count < 0)
    {
        abductee_count = 0;
    }
    if (abductee_count > abductee_capacity)
    {
        abductee_count = abductee_capacity;
    }
}
AbductorCraft::AbductorCraft(const AbductorCraft &other) : Aircraft(other), StealthAircraft(other), abductee_capacity(other.abductee_capacity), abductee_count(other.abductee_count)
{
    if (abductee_capacity <= 0)
    {
        abductee_capacity = 0;
        abductee_count = 0;
    }
    else
    {
        if (abductee_count > abductee_capacity)
        {
            abductee_count = abductee_capacity;
        }
        else if (abductee_count < 0)
        {
            abductee_count = 0;
        }
    }
}
void AbductorCraft::setAbducteeCount(int n)
{
    if (this->isCrashed())
    {
        return;
    }
    abductee_count = n;
    if (abductee_count < 0)
    {
        abductee_count = 0;
    }
    if (abductee_count > abductee_capacity)
    {
        abductee_count = abductee_capacity;
    }
}
void AbductorCraft::displayallinfo(ostream &os) const
{
    StealthAircraft::displayallinfo(os);
    os << "Abductee Count: " << abductee_count << "\nAbductee Capacity: " << abductee_capacity << endl;
}
void AbductorCraft::setAbducteeCapacity(int n)
{
    if (this->isCrashed())
    {
        return;
    }
    abductee_capacity = n;
    if (abductee_capacity < 0)
    {
        abductee_capacity = 0;
    }
}
int AbductorCraft::getAbducteeCount() const
{
    return abductee_count;
}
int AbductorCraft::getAbducteeCapacity() const
{
    return abductee_capacity;
}
// GuardianCraft methods
GuardianCraft::GuardianCraft() : Aircraft(), StealthAircraft(), CombatAircraft(), kill_count(0)
{
}
GuardianCraft::GuardianCraft(string name, int fuel, int hp, AircraftStatus status, string type, int count, int strength, bool cloak, int kills) : Aircraft(name, fuel, hp, status), CombatAircraft(name, fuel, hp, status, type, count, strength), StealthAircraft(name, fuel, hp, status, cloak), kill_count(kills)
{
    if (kill_count < 0)
    {
        kill_count = 0;
    }
}
GuardianCraft::GuardianCraft(const GuardianCraft &other) : Aircraft(other), StealthAircraft(other), CombatAircraft(other), kill_count(other.kill_count)
{
    if (kill_count < 0)
    {
        kill_count = 0;
    }
}
void GuardianCraft::displayallinfo(ostream &os) const
{
    Aircraft::displayallinfo(os);
    os << "Weapon Type: " << this->getWeaponType() << "\nWeapon Count: " << this->getWeaponCount() << "\nWeapon Strength: " << this->getWeaponStrength() << "\nCloak Status: " << ((this->getCloakStatus()) ? "On" : "Off") << "\nKill Count: " << kill_count << endl;
}
void GuardianCraft::setKillCount(int n)
{
    if (this->isCrashed())
    {
        return;
    }
    kill_count = n;
    if (kill_count < 0)
    {
        kill_count = 0;
    }
}
int GuardianCraft::getKillCount() const
{
    return kill_count;
}

// operator overloads
// aircraft operators
ostream &operator<<(ostream &os, const AircraftStatus &status)
{
    if (status == AircraftStatus::OnGround)
    {
        os << "On Ground";
    }
    else if (status == AircraftStatus::Airborne)
    {
        os << "Airborne";
    }
    else if (status == AircraftStatus::Crashed)
    {
        os << "Crashed";
    }
    return os;
}
Aircraft &Aircraft::operator+=(int n)
{
    if (this->isCrashed())
    {
        return *this;
    }
    if (current_status == AircraftStatus::OnGround)
    {
        fuel_level += n;
        if (fuel_level > 100)
        {
            fuel_level = 100;
        }
    }
    return *this;
}
Aircraft &Aircraft::operator-=(int n)
{
    if (this->isCrashed())
    {
        return *this;
    }
    if (current_status == AircraftStatus::OnGround)
    {
        fuel_level -= n;
        if (fuel_level < 0)
        {
            fuel_level = 0;
        }
    }
    return *this;
}
bool Aircraft::operator==(const Aircraft &other)
{
    if (this->fuel_level == other.fuel_level && this->current_status == other.current_status && this->health == other.health && this->identifier == other.identifier)
    {
        return true;
    }
    return false;
}
ostream &operator<<(ostream &os, const Aircraft &other)
{
    other.displayallinfo(os);
    return os;
}
istream &operator>>(istream &is, Aircraft &other)
{
    string identifier;
    int fuel;
    int hp;
    int status;
    cout << "Enter Identifier: ";
    is >> identifier;
    cout << "Enter Fuel Level (0-100): ";
    is >> fuel;
    cout << "Enter Health (0-100): ";
    is >> hp;
    do
    {
        cout << "Enter Status (0: OnGround, 1: Airborne, 2: Crashed): ";
        is >> status;
    } while (status < 0 || status > 2);
    other.setIdentifier(identifier);
    other.fuel_level = fuel;
    if (other.fuel_level < 0)
    {
        other.fuel_level = 0;
    }
    if (other.fuel_level > 100)
    {
        other.fuel_level = 100;
    }
    other.health = hp;
    if (other.health < 0)
    {
        other.health = 0;
    }
    if (other.health > 100)
    {
        other.health = 100;
    }
    if (other.fuel_level == 0 && other.current_status == AircraftStatus::Airborne)
    {
        other.health = 0;
    }
    if (other.health == 0)
    {
        other.current_status = AircraftStatus::Crashed;
    }
    if (status == 0)
    {
        other.current_status = AircraftStatus::OnGround;
    }
    else if (status == 1)
    {
        other.current_status = AircraftStatus::Airborne;
    }
    else if (status == 2)
    {
        other.current_status = AircraftStatus::Crashed;
    }
    return is;
}
// combat operators
CombatAircraft CombatAircraft::operator++(int)
{
    if (this->isCrashed())
    {
        return *this;
    }
    CombatAircraft temp(*this);
    if (this->getCurrentStatus() == AircraftStatus::OnGround)
    {
        this->setWeaponCount(this->getWeaponCount() + 1);
    }
    return temp;
}
CombatAircraft &CombatAircraft::operator--()
{
    if (this->isCrashed())
    {
        return *this;
    }
    if (this->getCurrentStatus() == AircraftStatus::OnGround)
    {
        this->setWeaponCount(this->getWeaponCount() - 1);
    }
    return *this;
}
// stealth operators
bool StealthAircraft::operator!()
{
    if (this->isCrashed())
    {
        return this->getCloakStatus();
    }
    if (this->getCloakStatus())
    {
        this->deactivateCloak();
    }
    else
    {
        this->activateCloak();
    }
    return this->getCloakStatus();
}

// abductor operators
bool AbductorCraft::operator>(const AbductorCraft &other)
{
    double c1 = abductee_count;
    double c2 = other.abductee_count;
    double cc1 = abductee_capacity;
    double cc2 = other.abductee_capacity;
    double ratio1 = c1 / cc1;
    double raito2 = c2 / cc2;
    return (ratio1 > raito2);
}
AbductorCraft &AbductorCraft::operator+=(int n)
{
    if (this->isCrashed())
    {
        return *this;
    }
    if (n > 0)
    {
        if (this->getCurrentStatus() == AircraftStatus::Airborne)
        {
            if ((n + abductee_count) <= (abductee_capacity))
            {
                abductee_count += n;
            }
            else
            {
                abductee_count = abductee_capacity;
            }
        }
        else
        {
            Aircraft::operator+=(n);
        }
    }
    return *this;
}
AbductorCraft &AbductorCraft::operator-=(int n)
{
    if (this->isCrashed())
    {
        return *this;
    }
    if (n > 0)
    {
        if (this->getCurrentStatus() == AircraftStatus::Airborne)
        {
            if (abductee_count >= n)
            {
                abductee_count -= n;
            }
            else
            {
                abductee_count = 0;
            }
        }
        else
        {
            Aircraft::operator-=(n);
        }
    }
    return *this;
}
AbductorCraft &AbductorCraft::operator&(AbductorCraft &other)
{
    if (this->isCrashed() || other.isCrashed())
    {
        return *this;
    }
    if (this->getCurrentStatus() == AircraftStatus::Airborne && other.getCurrentStatus() == AircraftStatus::Airborne)
    {
        if (abductee_capacity >= other.abductee_capacity)
        {
            this->setFuelLevel(this->getFuelLevel() + other.getFuelLevel());
            this->setHealth(this->getHealth() + other.getHealth());
            this->setAbducteeCapacity(abductee_capacity + other.abductee_capacity);
            this->setAbducteeCount(abductee_count + other.abductee_count);
            other.deactivateCloak();
            other.setAbducteeCount(0);
            other.setAbducteeCapacity(0);
            other.setFuelLevel(0);
        }
        else
        {
            other.setFuelLevel(this->getFuelLevel() + other.getFuelLevel());
            other.setHealth(this->getHealth() + other.getHealth());
            other.setAbducteeCapacity(abductee_capacity + other.abductee_capacity);
            other.setAbducteeCount(abductee_count + other.abductee_count);
            this->deactivateCloak();
            this->setAbducteeCount(0);
            this->setAbducteeCapacity(0);
            this->setFuelLevel(0);
        }
    }
    return *this;
}

// guardian operators
GuardianCraft GuardianCraft::operator++(int)
{
    if (this->isCrashed())
    {
        return *this;
    }
    GuardianCraft temp(*this);
    if (this->getCurrentStatus() == AircraftStatus::OnGround)
    {
        this->setWeaponCount(this->getWeaponCount() + 1);
    }
    return temp;
}
GuardianCraft &GuardianCraft::operator--()
{
    if (this->isCrashed())
    {
        return *this;
    }
    if (this->getCurrentStatus() == AircraftStatus::OnGround)
    {
        this->setWeaponCount(this->getWeaponCount() - 1);
    }
    return *this;
}
bool GuardianCraft::operator*=(const AbductorCraft &other)
{
    if ((this->getCurrentStatus() == AircraftStatus::Airborne) && (other.getCurrentStatus() == AircraftStatus::Airborne))
    {
        if (this->getWeaponCount() > 0)
        {
            if (other.getCloakStatus() == false && other.getAbducteeCount() == 0)
            {
                return true;
            }
        }
    }
    return false;
}
void GuardianCraft::operator*(AbductorCraft &other)
{
    if (*this *= other)
    {
        this->setWeaponCount(this->getWeaponCount() - 1);
        if(this->getWeaponCount() <= 0)
        {
            this->setWeaponCount(0);
        }
        other.setHealth(other.getHealth() - this->getWeaponStrength());
        if(other.getCurrentStatus() == AircraftStatus::Crashed)
        {
            this->setKillCount(this->getKillCount() + 1);
        }
    }
}

// helper
void Aircraft::displayallinfo(ostream &os) const
{
    os << "Identifier: " << identifier << "\nFuel Level: " << fuel_level << "%\nHealth: " << health << "%\nCurrent Status: " << this->getCurrentStatus() << endl;
}
