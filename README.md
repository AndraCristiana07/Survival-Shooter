
<!-- PROJECT LOGO -->
<br />
<div align="center">

  <h3 align="center">Survival Shooter</h3>

  <p align="center">
    A 2D top-down shooter game
    <br />
   
  </p>
</div>



<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknoledgments</a></li>
    
    
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<!-- [![Product Name Screen Shot][product-screenshot]](https://example.com) -->

In this simple 2D top-down survival shooter, your objective is to eliminate as many opponents as possible before your own defeat. Navigate the map full of obstacles and be careful because the opponents can shoot you back! You must avoid them and their bullets in order to avoid taking damage.

* Player :
The player is represented by several geometric primitives, suggestively positioned, so that the direction in which the player looks is clear. The direction in which the user looks is given by the mouse cursor. It moves on the X and Y axes (up, left, down, right), with the W, A, S, D keys.

* Camera :
The camera will permanently follow the player (the player will be drawn all the time in the center of the display window).  Only what is included in the viewport is seen in the display window.

* Enemy :
Enemies are still represented by simple geometric shapes, but with other colors/primitives, so that they differentiate themselves from the player. Enemies will spawn continuously throughout the game, either one at a time or in waves. Each enemy has a different movement speed. Enemies disappear when hit by a player's projectile. Enemies must continuously follow the player. 

* Gameplay :
The goal of the game is for the player to survive the enemies as long as possible. The player starts from a maximum health level. With each collision with an enemy, this level decreases. If the level drops to 0, then the player dies and the game ends.




### Built With

These are what I used to build the bot:

* ![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
* ![OpenGL](https://img.shields.io/badge/OpenGL-%23FFFFFF.svg?style=for-the-badge&logo=opengl)
* ![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)



<!-- GETTING STARTED -->
## Getting Started

To be able to use this project you will need some stuff first.

### Prerequisites

* cmake
  [Cmake Installation steps](https://cgold.readthedocs.io/en/latest/first-step/installation.html)
* OpenGL






<!-- USAGE EXAMPLES -->
<!-- ## Usage

Use this space to show useful examples of how a project can be used. Additional screenshots, code examples and demos work well in this space. You may also link to more resources.

_For more examples, please refer to the [Documentation](https://example.com)_

<p align="right">(<a href="#readme-top">back to top</a>)</p> -->



<!-- ROADMAP -->
## Roadmap

- [x] Make a window where to render stuff
- [x] Make the player
- [x] Binding keys
- [x] Camera
- [x] Make the map
- [x] Make opponents
- [x] Make opponents follow player
- [x] Make ammo and health for player and opponents
- [x] Collisions
 


<!-- CONTACT -->
## Contact

Andra -  tapornadra@gmail.com

Project Link: https://github.com/AndraCristiana07/Survival-Shooter




<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

Some things that helped me while making this project :
* [Learn OpenGL](https://learnopengl.com/)





