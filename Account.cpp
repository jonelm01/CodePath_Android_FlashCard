/****************************************************************************************************************************
Title         :   Account.hpp
Author        :   Dream Team
Description   :   header/interface files for Account class
****************************************************************************************************************************/
/*
Account Class
Jonel Muncan
11/21/22
defines member methods and variables of Account 
Contains: parameterized constructor, mutator, accessors, display function, network template related accessors and mutators
*/

#include "Account.hpp"

//default constructor
//@post:  set username and password to ""
//        creates an empty vector of post objects to store into feed_
Account::Account()
{
    username_ = "";
    password_ = "";
    posts_ = LinkedList<Post*>();
    following_ = {};
}


/**
    Parameterized Constructor
    @param username  : username of the account, stored into username_
    @param password  : password of the account, stored into password_
    @post:             sets the private members to the value of the parameters
*/
Account::Account(std::string username, std::string password) : username_(username), password_(password), posts_(LinkedList<Post*>()), following_({}), net_(nullptr) { }

/**
  @return:     the username of the Account
*/
std::string Account::getUsername() const { return username_; }


/**
  @param:     a reference to the username of the Account
  @psot:      sets the parameter to the value of the private member
*/
void Account::setUsername(const std::string& username) { username_ = username; }


/**
  @return:     the password of the Account
*/
std::string Account::getPassword() const { return password_; }


/**
  @param a reference to the password of the Account
  @post:      sets the private member to the value of the parameter
*/
void Account::setPassword(const std::string& password) { password_ = password; }


/**
      Accessor function
      @return           :   the pointer to the Network the account is in
   */
Network<Account>* Account::getNetwork() const { return net_; }


/**
      Mutator function
      @param            :   a pointer to a Network
      @post             :   the Network pointer private member points to the input Network
   */
void Account::setNetwork(Network<Account>* network) { net_ = network; }


/**
    @param newPost   : The pointer to the Post object that will be added to its list
    @return          : Will return true if a post gets added sucesfully to the vector

    @post:           " Adds post to posts_ and its Networks feed_
*/
bool Account::addPost(Post* newPost){
    posts_.insert(newPost, 0);
    net_->addToFeed(newPost);
    if(newPost ->getLikes() > maxLikes_){
        maxLikes_ = newPost->getLikes();
        maxLikesPost_ = newPost;
    }
    if (newPost -> getLikes() <= minLikes_){ //<?
        minLikes_ = newPost->getLikes();
        minLikesPost_ = newPost;
    }

    if(newPost->getPriority() == Post::priority::LOW){ //LOW
        lowPriority_.push_back(newPost);
    }
    else if(newPost->getPriority() ==Post::priority::MEDIUM){ //MEDIUM
        medPriority_.push_back(newPost);
    }
    else if(newPost->getPriority() ==Post::priority::HIGH){ //HIGH
        highPriority_.push_back(newPost);
    }
    return true;
}


/*
    @post:      Prints the feed_ that contains the post objects by calling their display function
*/
void Account::viewPosts() const {

    Node<Post*>* itt = posts_.getHeadPtr();

    while (itt != nullptr) {
        itt->getItem()->displayPost();
        itt = itt->getNext();
    }

}



/**
      @param            :   the username of the Account to follow
      @return           :   true if the account was successfully able to follow, false otherwise
      @post             :   adds the username to the vector of following accounts only if
                            it is affiliated to a Network AND it is not already following an account
                            with the same username.
   */
bool Account::followAccount(const std::string username){

    bool exists = false;

    for(std::string un : following_) {
        if(un == username) {
            exists = true;
        }
    }

    if(!exists && net_ != nullptr) {
        following_.push_back(username);
        return true;
    }

    return false;
}


/**
      @return           :   the vector of usernames the Account is following
   */
std::vector<std::string> Account::viewFollowing() const {
    return following_;
}


/**
  @return           :  true if account has same private members as parameter,
                       false otherwise
*/
bool Account::operator==(const Account &acc) const {
    if(acc.getUsername() == this->username_ && acc.getPassword() == this->password_) {
        return true;
    }

    return false;
}

std::vector<Post*> Account::increasingPriorityOldestToNewestHELPER(){
    std::vector<Post*> vec;
    for(int i=0; i<lowPriority_.size();i++){
        vec.push_back(lowPriority_[i]);
    }
    for(int j=0; j<medPriority_.size();j++){
        vec.push_back(medPriority_[j]);
    }
    for(int k=0; k<highPriority_.size();k++){
        vec.push_back(highPriority_[k]);
    }
    return vec;
}

std::vector<Post*> Account::increasingPriorityNewestToOldestHELPER(){
   std::vector<Post*> vec;
   for(int i= lowPriority_.size()-1; i>=0;i--){
       vec.push_back(lowPriority_[i]);
   }
   for(int j= medPriority_.size()-1; j>=0;j--){
       vec.push_back(medPriority_[j]);
   }
   for(int k= highPriority_.size()-1; k>=0;k--){
       vec.push_back(highPriority_[k]);
   }
    return vec;
}

std::vector<Post*> Account::decreasingPriorityOldestToNewestHELPER(){
    std::vector<Post*> vec; 
    for(int i=0; i<highPriority_.size();i++){
        vec.push_back(highPriority_[i]);
    }
    for(int j=0; j<medPriority_.size();j++){
        vec.push_back(medPriority_[j]);
    }
    for(int k=0; k<lowPriority_.size();k++){
        vec.push_back(lowPriority_[k]);
    }
    return vec;
}


std::vector<Post*> Account::decreasingPriorityNewestToOldestHELPER(){
   std::vector<Post*> vec;
   for(int k= highPriority_.size()-1; k>=0;k--){
       vec.push_back(highPriority_[k]);
   }
   for(int j= medPriority_.size()-1; j>=0;j--){
       vec.push_back(medPriority_[j]);
   }
    for(int i= lowPriority_.size()-1; i>=0;i--){
       vec.push_back(lowPriority_[i]);
   }
   return vec;
}



void Account::findMinLikes(){
    minLikes_ = 10000;
    std::vector<Post*> temp = increasingPriorityOldestToNewest();
    for(int i=0; i<temp.size(); i++){
        Post* curr = temp[i];
        if(curr->getLikes() <= minLikes_){
            minLikes_ = curr->getLikes();
            minLikesPost_ = curr;
        }
    }
}


void Account::findMaxLikes(){
    maxLikes_ = -1;
    std::vector<Post*> temp = decreasingPriorityNewestToOldest();
    for(int i=0; i<temp.size(); i++){
        Post* curr = temp[i];
        if(curr->getLikes() >= maxLikes_){
            maxLikes_ = curr->getLikes();
            maxLikesPost_ = curr;
        }
    }
}



/*
@param            :   A pointer to a Post
@return           :   True iff the Post was successfully found and removed,
                      false othewise.
@post             :   Removes the given Post from its list
                      as well as from the Network's feed.
*/
bool Account::removePost(Post* post){
    int postPosition = posts_.getIndexOf(post);
    bool minlike = false;
    bool maxlike = false;


    if (postPosition > -1) {
        posts_.remove(postPosition);
        net_->removePostFromFeed(post);
        if(post->getPriority() == Post::priority::LOW){
            if(minLikesPost_ == post){
                minlike = true;
            }
            if(maxLikesPost_ == post){
                maxlike = true;
            }
            for(int i=0; i<lowPriority_.size(); i++){
                if(lowPriority_[i] == post){
                    lowPriority_.erase(lowPriority_.begin() + (i)); 
                }
            }

            if(minlike == true){
                findMinLikes();
            }
            if(maxlike == true){
                findMaxLikes();
            }  
        }
        else if(post->getPriority() == Post::priority::MEDIUM){
            if(minLikesPost_ == post){
                minlike = true;
            }
            if(maxLikesPost_ == post){
                maxlike = true;
            }
            for(int i=0; i<medPriority_.size(); i++){
                if(medPriority_[i] == post){
                    medPriority_.erase(medPriority_.begin() + (i));
                }
            }

            if(minlike == true){
                findMinLikes();
            }
            if(maxlike == true){
                findMaxLikes();
            }  
        }
        else if(post->getPriority() == Post::priority::HIGH){
            if(minLikesPost_ == post){
                minlike = true;
            }
            if(maxLikesPost_ == post){
                maxlike = true;
            }
            for(int i=0; i<highPriority_.size(); i++){
                if(highPriority_[i] == post){
                    highPriority_.erase(highPriority_.begin() + (i));
                }
            }

            if(minlike == true){
                findMinLikes();
                //minLikes_ = minLikesPost_->getLikes();
            }
            if(maxlike == true){
                findMaxLikes();
            }  
        }

        return true;
    }
    return false;
}



Post* Account::getMinLikes(){
    return minLikesPost_;
}

Post* Account::getMaxLikes(){
    return maxLikesPost_;
}



std::vector<Post*> Account::increasingPriorityOldestToNewest(){
    std::vector<Post*> vect = increasingPriorityOldestToNewestHELPER();
    return vect;
}


std::vector<Post*> Account::increasingPriorityNewestToOldest(){
   std::vector<Post*> vect = increasingPriorityNewestToOldestHELPER();
    return vect;
}



std::vector<Post*> Account::decreasingPriorityOldestToNewest(){
    std::vector<Post*> vect = decreasingPriorityOldestToNewestHELPER();
    return vect;
}



std::vector<Post*> Account::decreasingPriorityNewestToOldest(){
   std::vector<Post*> vect = decreasingPriorityNewestToOldestHELPER();
   return vect;
}



/*
@param            :   Pointer to a Post object
@param            :   The new title of the Post (or an empty string if you do not
                      want to change it)
@param            :   The new body of the Post (or an empty string if you do not
                      want to change it)

@post            :   This function will take the Post and given the new title and body,
                     update the Posts title and body as appropriate. It will also update
                     the `timestamp_` to the current time of the update. This function should then
                     update the location of the Post in its list of `posts_` to the front of the list
                     as well as utilizing its Network pointer to do the same in the `feed_`.
*/
bool Account::updatePost(Post* post, std::string new_title, std::string new_body) {
    if(new_title != "") { post->setTitle(new_title); }

    if(new_body != "") { post->setBody(new_body); }

    post->updateTimeStamp();

    bool max = false;
    bool min = false;

    if(post == maxLikesPost_){
        max = true;
    }
    if(post == minLikesPost_){
        min = true;
    }

    if(post->getPriority() == Post::priority::LOW){
        lowPriority_.push_back(post);
        for(int i=0; i<lowPriority_.size(); i++){
                if(lowPriority_[i] == post){
                    lowPriority_.erase(lowPriority_.begin() + (i)); //////////////////i-1??? unsure atm
                    break;
                }
            }
        if(min == true){
            findMinLikes();
                //minLikes_ = minLikesPost_->getLikes();
        }
        if(max == true){
            findMaxLikes();
        }  
    }
    else if(post->getPriority() == Post::priority::MEDIUM){
        medPriority_.push_back(post);
        for(int i=0; i<medPriority_.size(); i++){
                if(medPriority_[i] == post){
                    medPriority_.erase(medPriority_.begin() + (i)); 
                    break;
                }
            }
        if(min == true){
            findMinLikes();
        }
        if(max == true){
            findMaxLikes();
        }  
    }
    else if(post->getPriority() == Post::priority::HIGH){
        highPriority_.push_back(post);
        for(int i=0; i<highPriority_.size(); i++){
                if(highPriority_[i] == post){
                    highPriority_.erase(highPriority_.begin() + (i)); 
                    break;
                }
            }
        if(min == true){
            findMinLikes();
        }
        if(max == true){
            findMaxLikes();
        }  
    }

    return net_->updateFeed(post);
}

