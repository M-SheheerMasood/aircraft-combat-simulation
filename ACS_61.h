#ifndef ACS_61_H
#define ACS_61_H

#include <iostream>
#include <string>
using namespace std;
/*
Include only ATTRIBUTES and FUNCTION SIGNATURES for each class in this file.
Code for each method must be in ACS_61.cpp
i.e.
class Aeroplane {
    private:
        string name;
    public:
        string get_name();
};
*/

enum class AircraftStatus
{
    OnGround,
    Airborne,
    Crashed
};

// BASE CLASS
class Aircraft
{
private:
    string identifier;
    int fuel_level;
    int health;
    AircraftStatus current_status;
    //
protected:
    virtual void displayallinfo(ostream &os) const;
public:
    Aircraft();
    Aircraft(string name, int fuel, int hp, AircraftStatus status);
    Aircraft(const Aircraft &other);
    void setHealth(int n);
    void setFuelLevel(int n);
    void setIdentifier(string n);
    bool isCrashed();
    string getIdentifier() const;
    int getFuelLevel() const;
    int getFuelCapacity() const;
    int getHealth() const;
    AircraftStatus getCurrentStatus() const;
    virtual void takeOff();
    virtual void land();
    friend ostream &operator<<(ostream &os, const AircraftStatus &status);
    Aircraft &operator+=(int n);
    Aircraft &operator-=(int n);
    bool operator==(const Aircraft &other);
    friend ostream &operator<<(ostream &os, const Aircraft &other);
    friend istream &operator>>(istream &is, Aircraft &other);
};

// INHERITED CLASSES -- implement inheritance yourself.
class CombatAircraft : virtual public Aircraft
{
private:
    string weapon_type;
    int weapon_count;
    int weapon_strength;
    //
protected:
    void displayallinfo(ostream &os) const override;
public:
    CombatAircraft();
    CombatAircraft(string name, int fuel, int hp, AircraftStatus status, string type, int count, int strength);
    CombatAircraft(const CombatAircraft &other);
    void setWeaponType(string n);
    void setWeaponCount(int n);
    void setWeaponStrength(int n);
    string getWeaponType() const;
    int getWeaponCount() const;
    int getWeaponStrength() const;
    CombatAircraft operator++(int);
    CombatAircraft &operator--();
};

class StealthAircraft : virtual public Aircraft
{
private:
    bool cloak_status;
    //
protected:
    void displayallinfo(ostream &os) const override;
public:
    StealthAircraft();
    StealthAircraft(string name, int fuel, int hp, AircraftStatus status, bool cloak);
    StealthAircraft(const StealthAircraft &other);
    bool getCloakStatus() const;
    void activateCloak();
    void deactivateCloak();
    void takeOff() override;
    void land() override;
    bool operator!();
};

class AbductorCraft : virtual public StealthAircraft
{
private:
    int abductee_count;
    int abductee_capacity;
    //
protected:
    void displayallinfo(ostream &os) const override;
public:
    AbductorCraft();
    AbductorCraft(string name, int fuel, int hp, AircraftStatus status, bool cloak, int count, int capacity);
    AbductorCraft(const AbductorCraft &other);
    void setAbducteeCount(int n);
    void setAbducteeCapacity(int n);
    int getAbducteeCount() const;
    int getAbducteeCapacity() const;
    bool operator>(const AbductorCraft &other);
    AbductorCraft &operator+=(int n);
    AbductorCraft &operator-=(int n);
    AbductorCraft &operator&(AbductorCraft &other);
};

class GuardianCraft : public StealthAircraft, public CombatAircraft
{
private:
    int kill_count;
    //
protected:
    void displayallinfo(ostream &os) const override;
public:
    GuardianCraft();
    GuardianCraft(string name, int fuel, int hp, AircraftStatus status, string type, int count, int strength, bool cloak, int kills);
    GuardianCraft(const GuardianCraft &other);
    void setKillCount(int n);
    int getKillCount() const;
    GuardianCraft operator++(int);
    GuardianCraft &operator--();
    bool operator*=(const AbductorCraft& other);
    void operator*(AbductorCraft& other);
};

#endif