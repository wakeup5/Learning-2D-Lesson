#include "stdafx.h"
#include "Player.h"


Player::Player()
{

}


Player::~Player()
{
}

bool Player::fire()
{
	switch (_weaponMode)
	{
	case 0:
		return fireBasic();
	case 1:
		return fireSpecial1();
	}

	return false;
}

bool Player::fireBasic()
{
	if (_cooltimeBasic <= 0)
	{
		for (int i = 0; i < _maxBasic; i++)
		{
			if (_basicBullets[i].getIsFire()) continue;

			_basicBullets[i].setPosition(makePoint(this->getPosition().x, this->getPosition().y - _width));
			_basicBullets[i].setIsFire(true);
			_cooltimeBasic = COOLTIME_BASIC;
			return true;
		}
	}
	else if (_cooltimeBasic > 0)
	{
		_cooltimeBasic -= 10;
	}
	
	return false;
}


bool Player::fireSpecial1()
{
	if (_cooltimeSpecial1 <= 0)
	{
		int j = 0;
		Missile *selectMissile[5];
		for (int i = 0; i < _maxSpecial1 && j < 5; i++)
		{
			if (!_special1Bullets[i].getIsFire())
			{
				selectMissile[j] = &_special1Bullets[i];
				j++;
			}
		}

		if (j == 5)
		{
			for (int i = 0; i < 5; i++)
			{
				selectMissile[i]->setPosition(makePoint(this->getPosition().x, this->getPosition().y - _width));
				selectMissile[i]->setDegree(30 - (15 * i));
				selectMissile[i]->setIsFire(true);
			}
			_cooltimeSpecial1 = COOLTIME_SPECIAL_1;
			return true;
		}
	}
	else if (_cooltimeSpecial1 > 0)
	{
		_cooltimeSpecial1 -= 10;
	}
	return false;
}


void Player::update()
{
	for (int i = 0; i < _maxBasic; i++)
	{
		if (!_basicBullets[i].getIsFire()) continue;
		_basicBullets[i].move();

		if (_basicBullets[i].getPosition().y < 0) _basicBullets[i].setIsFire(false);
	}

	for (int i = 0; i < _maxSpecial1; i++)
	{
		if (_special1Bullets[i].getIsFire())
		{
			_special1Bullets[i].move();
			if (_special1Bullets[i].getPosition().y < 0) _special1Bullets[i].setIsFire(false);
		}
	}

}

void Player::printBullet(HDC hdc)
{
	for (int i = 0; i < _maxBasic; i++)
	{
		if (!_basicBullets[i].getIsFire()) continue;
		drawEllipse(hdc, _basicBullets[i].getSize());
	}

	for (int i = 0; i < _maxSpecial1; i++)
	{
		if (!_special1Bullets[i].getIsFire()) continue;
		drawEllipse(hdc, _special1Bullets[i].getSize());
	}
	
}

void Player::setMode(int i)
{
	if (i == 1 || i == 2 || i == 3 || i == 4)
	{
		_weaponMode = i;
	}
	else
	{
		_weaponMode = 0;
	}
}