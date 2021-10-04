//
// Created by logan on 10/4/2021.
//

#include "Converter.h"

string Converter::decimalToRoman(vector<Numeral> numerals, string input) {
    int remainder = this->number;
    for (int i = 0; i < numerals.size(); ++i) {
        remainder = getSymbolQuantities(numerals.at(i), remainder, numerals);
    }
    return this->numeral;
}

int Converter::getSymbolQuantities(Numeral numeralPassedIn, int remainder, vector<Numeral> numerals) {
    int amountContained = remainder / numeralPassedIn.getValue();
    if (amountContained > 0) {
        if (amountContained == 4) {
            for (int j = 0; j < numerals.size(); ++j) {
                if (numerals.at(j).getValue() == numeralPassedIn.getValue()) {
                    string letter = numerals.at(j - 1).getNumeralRep();
                    this->numeral.append(numeralPassedIn.getNumeralRep());
                    this->numeral.append(letter);
                }
            }
        } else {
            this->numeral.append(numeralPassedIn.getNumeralRep());
        }
    }

    for (int j = 0; j < numerals.size(); ++j) {
        for (int i = 0; i < numerals.size(); ++i) {
            if ((numerals.at(j).getValue() - numerals.at(i).getValue()) == remainder) {
                this->numeral.append(numerals.at(i).getNumeralRep());
                this->numeral.append(numerals.at(j).getNumeralRep());
                remainder = remainder - numerals.at(j).getValue() - numerals.at(i).getValue();
                return remainder;
            }
        }
    }
    if (amountContained == 0) {
        return remainder;
    }
    remainder = remainder % numeralPassedIn.getValue();
    return remainder;
}

int Converter::romanToDecimal(vector<Numeral> numerals, string input) {
    int number = 0;
    if (input.length() == 1) {
        for (int j = 0; j < numerals.size(); ++j) {
            if (input.at(0) == numerals.at(j).getNumeralRep().at(0)) {
                this->number = numerals.at(j).getValue();
                return this->number;
            }
        }
    }
    if (input.size() > 1) {
        vector<pair<char, char> > vecOfPairs;
        if (input.size() % 2 == 0) {
            for (int i = 0; i < input.size(); i = i + 2) {
                pair<char, char> aPair;
                aPair.first = input.at(i);
                aPair.second = input.at(i + 1);
                vecOfPairs.push_back(aPair);
            }

            for (int j = 0; j < vecOfPairs.size(); ++j) {
                this->number += evaluatePairs(numerals, vecOfPairs.at(j));
            }
        } else {
            string lastNumeral = input.substr(input.size() - 1);
            input = input.substr(0, input.size() - 1);

            for (int i = 0; i < input.size(); i = i + 2) {
                pair<char, char> aPair;
                aPair.first = input.at(i);
                aPair.second = input.at(i + 1);
                vecOfPairs.push_back(aPair);
            }

            for (int j = 0; j < vecOfPairs.size(); ++j) {
                this->number += evaluatePairs(numerals, vecOfPairs.at(j));
            }
            int lastExtraNumberToAdd = 0;
            for (int z = 0; z < numerals.size(); ++z) {
                if (lastNumeral == numerals.at(z).getNumeralRep()) {
                    lastExtraNumberToAdd = numerals.at(z).getValue();
                }
            }
            this->number += lastExtraNumberToAdd;
        }
    }
    return this->number;
}

int Converter::evaluatePairs(vector<Numeral> numerals, pair<char, char> aPair) {
    pair<int, int> numPair;
    for (int i = 0; i < numerals.size(); ++i) {
        if (numerals.at(i).getNumeralRep().at(0) == aPair.first) {
            numPair.first = numerals.at(i).getValue();
        }
        if (numerals.at(i).getNumeralRep().at(0) == aPair.second) {
            numPair.second = numerals.at(i).getValue();
        }
    }
    int sum = 0;
    if (numPair.first >= numPair.second) {
        sum = numPair.first + numPair.second;
    } else {
        sum = numPair.second - numPair.first;
    }
    return sum;
}


const string &Converter::getNumeral() const {
    return numeral;
}

void Converter::setNumeral(const string &numeral) {
    Converter::numeral = numeral;
}

int Converter::getNumber() const {
    return number;
}

void Converter::setNumber(int number) {
    Converter::number = number;
}
