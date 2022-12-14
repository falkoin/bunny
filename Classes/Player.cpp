//
//  Player.cpp
//  bunny
//
//  Created by Falko Döhring on 26.08.15.
//
//

#include "Player.h"
#include "Globals.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Player::Player()
{
}

Player::~Player()
{
}

Player* Player::create()
{
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprites-0001-default.plist");
    Player* pSprite = new Player();
    
    if (pSprite->initWithSpriteFrameName("playerIdle.png"))
    {
        pSprite->initOptions();
        pSprite->autorelease();
        pSprite->getTexture()->setAliasTexParameters();
        pSprite->setScale(SCALE_FACTOR);
        pSprite->setFlippedX(false);
        pSprite->setAnchorPoint(Point(0,0));
        
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

void Player::initOptions()
{
    state = State::Idle;
    _velocity = Point(0,0);
    AnimationCache::getInstance()->addAnimationsWithFile("player-animations.plist");
    
    // idle animation
    _idleCache = AnimationCache::getInstance();
    _idleAnimation = _idleCache->getAnimation("idle");
    _idleAnimation->setRestoreOriginalFrame(false);
    
    idleAnimation = RepeatForever::create(Animate::create(_idleAnimation));
    idleAnimation->retain();
//    runAction(idleAnimation);
    
    // happy animation
    _happyCache = AnimationCache::getInstance();
    _happyAnimation = _happyCache->getAnimation("happy");
    _happyAnimation->setRestoreOriginalFrame(false);
    
    happyAnimation = Animate::create(_happyAnimation);
    happyAnimation->retain();
    
    // win animation
    _winCache = AnimationCache::getInstance();
    _winAnimation = _winCache->getAnimation("win");
    _winAnimation->setRestoreOriginalFrame(true);
    
    winAnimation = RepeatForever::create(Animate::create(_winAnimation));
    winAnimation->retain();
    
    // cry animation
    _cryCache = AnimationCache::getInstance();
    _cryAnimation = _cryCache->getAnimation("cry");
    _cryAnimation->setRestoreOriginalFrame(true);
    
    cryAnimation = RepeatForever::create(Animate::create(_cryAnimation));
    cryAnimation->retain();

//    auto fileUtiles = FileUtils::getInstance();
//    auto fragmentFullPath = fileUtiles->fullPathForFilename("wind.fsh");
//    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
//    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
//
//    
//    _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
//    _glprogramstate->retain();
//    _glprogramstate->setUniformFloat("u_wind", 1.0f);
//    this->setGLProgramState(_glprogramstate);
    
//    auto fileUtiles = FileUtils::getInstance();
//    auto fragmentFullPath = fileUtiles->fullPathForFilename("example_Noisy.fsh");
//    auto fragSource = fileUtiles->getStringFromFile(fragmentFullPath);
//    auto glprogram = GLProgram::createWithByteArrays(ccPositionTextureColor_noMVP_vert, fragSource.c_str());
//    
//    
//    auto _glprogramstate = GLProgramState::getOrCreateWithGLProgram(glprogram);
//    _glprogramstate->retain();
//    auto s = this->getTexture()->getContentSizeInPixels();
//    _glprogramstate->setUniformVec2("resolution", Vec2(s.width, s.height));
//    this->setGLProgramState(_glprogramstate);
}

void Player::setPlayerVelocity(cocos2d::Vec2 velocity)
{
    _velocity = velocity;
}

Vec2 Player::getPlayerVelocity()
{
    return _velocity;
}

void Player::moveUp()
{
    _velocity.y = PLAYER_MAX_JUMP_VELOCITY * SCALE_FACTOR;
}
void Player::moveUpDouble()
{
    _velocity.y = PLAYER_MAX_JUMP_VELOCITY * 2 * SCALE_FACTOR;
}

void Player::moveRight(float factor)
{
//    if (_velocity.x < 0)
//        _velocity.x = 0;
//    if (_velocity.x > (PLAYER_MAX_VELOCITY * SCALE_FACTOR) * 0.25)
//        _velocity.x = _velocity.x + 0.075f;
//    else if (_velocity.x > (PLAYER_MAX_VELOCITY * SCALE_FACTOR) * 0.5)
//        _velocity.x = _velocity.x + 0.100f;
//    else if (_velocity.x > (PLAYER_MAX_VELOCITY * SCALE_FACTOR) * 0.75)
//        _velocity.x = _velocity.x + 0.125f;
//    else
//        _velocity.x = _velocity.x + 0.075f;
//    if (_velocity.x >= PLAYER_MAX_VELOCITY * SCALE_FACTOR)
//    {
//        _velocity.x = PLAYER_MAX_VELOCITY * SCALE_FACTOR;
//    }
    
    _velocity.x = factor*5*SCALE_FACTOR;
    if (_velocity.x >= PLAYER_MAX_VELOCITY * SCALE_FACTOR)
    {
        _velocity.x = PLAYER_MAX_VELOCITY * SCALE_FACTOR;
    }
    else if (_velocity.x <= -PLAYER_MAX_VELOCITY * SCALE_FACTOR)
    {
        _velocity.x = -PLAYER_MAX_VELOCITY * SCALE_FACTOR;
    }
}

void Player::moveLeft(float factor)
{
    if (_velocity.x > 0)
        _velocity.x = 0;
    if (_velocity.x < (-PLAYER_MAX_VELOCITY * SCALE_FACTOR) * 0.25)
        _velocity.x = _velocity.x - 0.075f;
    else if (_velocity.x < (-PLAYER_MAX_VELOCITY * SCALE_FACTOR) * 0.5)
        _velocity.x = _velocity.x - 0.100f;
    else if (_velocity.x < (-PLAYER_MAX_VELOCITY * SCALE_FACTOR) * 0.75)
        _velocity.x = _velocity.x - 0.125f;
    else
        _velocity.x = _velocity.x - 0.075f;
    if (_velocity.x <= -PLAYER_MAX_VELOCITY * SCALE_FACTOR)
    {
        _velocity.x = -PLAYER_MAX_VELOCITY * SCALE_FACTOR;
    }
}

void Player::stop()
{
    _velocity.x = 0.0f;
}

void Player::idle()
{
}

void Player::win()
{
    if (state != State::Win)
    {
        runAction(winAnimation);
        state = State::Win;
    }
}

void Player::falling()
{
}

void Player::animate()
{
    if (_velocity.y > 0 && _velocity.y <= PLAYER_MAX_JUMP_VELOCITY * SCALE_FACTOR)
    {
        if (state != State::Jumping && state != State::Win)
        {
            this->setSpriteFrame("playerHappy.png");
            state = State::Jumping;
        }
    }
    if (_velocity.y > 0 && _velocity.y > PLAYER_MAX_JUMP_VELOCITY * SCALE_FACTOR)
    {
        if (state != State::SuperJumping && state != State::Win)
        {
            this->setSpriteFrame("playerSuperhappy.png");
            state = State::SuperJumping;
        }
    }
    else if (_velocity.y < 0 && _velocity.y > MAX_GRAVITY * SCALE_FACTOR * 0.65)
    {
        if (state != State::Idle && state != State::Win)
        {
            this->setSpriteFrame("playerIdle.png");
            state = State::Idle;
        }
    }
    else if (_velocity.y <= MAX_GRAVITY * SCALE_FACTOR * 0.65 && _velocity.y > MAX_GRAVITY * SCALE_FACTOR)
    {
        if (state != State::Falling && state != State::Win)
        {
            this->setSpriteFrame("playerUnhappy.png");
            state = State::Falling;
        }
    }
    else if (_velocity.y <= MAX_GRAVITY * SCALE_FACTOR)
    {
        if (state != State::FallingDeep && state != State::Win)
        {
            this->setSpriteFrame("playerCrying.png");
            state = State::FallingDeep;
        }
    }
}

void Player::setShader(float val)
{
    _glprogramstate->setUniformFloat("u_wind", val);
}

void Player::warpPlayer()
{
    auto delayAction = DelayTime::create(1);
    auto warpAction = MoveBy::create(2, Point(0,this->getContentSize().height*SCALE_FACTOR*2));
    auto setVar  = CallFunc::create([this]() {this->warpCallback();});
    auto sequenceAction = Sequence::create(delayAction, setVar, warpAction, NULL);
    this->runAction(sequenceAction);

}

void Player::warpCallback()
{
    auto teleporter = Sprite::createWithSpriteFrameName("teleporter.png");
    teleporter->setAnchorPoint(Point(0.5,0.3));
    this->addChild(teleporter);
    teleporter->setGlobalZOrder(Z_TELE);
    teleporter->setPosition(this->getContentSize().width*0.5-1,0);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("teleport.wav");
}

void Player::playerDeath()
{
    auto scaleAction = ScaleBy::create(0.05, 1, 0);
    auto removeAction = RemoveSelf::create();
    auto deathSequence = Sequence::create(scaleAction, removeAction, NULL);
    this->runAction(deathSequence);
}