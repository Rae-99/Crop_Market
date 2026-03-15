#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Crop {
private:
    string name, soil, water, temperature, season;

public:
    Crop(string n, string s, string w, string t, string se)            //Constructor
        : name(n), soil(s), water(w), temperature(t), season(se) {}

    string getName() const {                                           //Getters
        return name; 
    }
    string getSoil() const { 
        return soil; 
    }
    string getWater() const { 
        return water; 
    }
    string getTemperature() const {
        return temperature; 
    }
    string getSeason() const { 
        return season; 
    }
};

int calculateScore(const Crop& c, const string& soil, const string& water,
                   const string& temp, const string& season) {
    int score = 0;

    if (c.getSoil() == soil)   
        score += 3;
    if (c.getWater() == water)  
        score += 2;
    if (c.getTemperature() == temp) 
        score += 2;
    if (c.getSeason() == season) 
        score += 3;

    return score;
}

int main() {
    vector<Crop> crops;
    crops.push_back(Crop("Rice", "high", "high", "high", "monsoon"));
    crops.push_back(Crop("Wheat", "high", "moderate", "moderate", "winter"));
    crops.push_back(Crop("Maize", "moderate", "moderate", "moderate", "summer"));
    crops.push_back(Crop("Millets", "low", "low", "high", "summer"));
    crops.push_back(Crop("Sugarcane", "high", "high", "high", "monsoon"));



    string soil, water, temp, season;

    cout << "Enter soil fertility: ";  
    cin >> soil;
    cout << "Enter water supply: ";    
    cin >> water;
    cout << "Enter temperature: ";     
    cin >> temp;
    cout << "Enter season: ";          
    cin >> season;

    cout << "\nRecommended Crops:\n";

    for (const Crop& c : crops) {
        int score = calculateScore(c, soil, water, temp, season);
        if (score >= 6)
            cout << c.getName() << " (Score: " << score << ")\n";
    }

    return 0;
}