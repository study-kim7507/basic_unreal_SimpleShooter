<https://www.udemy.com/course/unrealcourse/?couponCode=ST20MT50724>

❗ 언리얼엔진 학습을 위해 유데미 강의를 참고해서 만든 FPS 프로토타입 게임입니다.

❗ 해당 프로젝트를 기반, 여러 아이디어를 바탕으로 게임을 제작하는 다양한 프로젝트를 수행하고자 합니다.

❗ 2023년 12월 제작, 애셋의 저작권과 용량의 문제로 재업로드 합니다.  

<br/>
<br/>

## 개발환경 📚
> <img src="https://img.shields.io/badge/Enviroment-%23121011?style=for-the-badge"> <img src="https://img.shields.io/badge/visual studio-5C2D91?style=for-the-badge&logo=visualstudio&logoColor=white"><img src="https://img.shields.io/badge/git-F05032?style=for-the-badge&logo=git&logoColor=white">

> <img src="https://img.shields.io/badge/Development-%23121011?style=for-the-badge"><img src="https://img.shields.io/badge/unreal engine-0E1128?style=for-the-badge&logo=unrealengine&logoColor=white">

> <img src="https://img.shields.io/badge/Reference-%23121011?style=for-the-badge"><img src="https://img.shields.io/badge/udemy-A435F0?style=for-the-badge&logo=udemy&logoColor=white">

> <img src="https://img.shields.io/badge/Communication-%23121011?style=for-the-badge"><img src="https://img.shields.io/badge/notion-000000?style=for-the-badge&logo=notion&logoColor=white">

<br/>
<br/>

## 프로젝트 구조 🌲
### Unreal Behavior Tree
- 언리얼엔진의 인공지능 제작에서 사용되는 비헤이비어 트리를 이용하여 적 캐릭터가 플레이어 캐릭터를 쫓아오도록 구현
- 만약, 일정 반경 범위 내에 플레이어 캐릭터가 있다면 사격 실시
- 해당 캐릭터가 플레이어 캐릭터를 찾을 수 없다면 최초 스폰 위치로 되돌아가도록 구현

  ```
  1. BTService_PlayerIfSeen.cpp
  2. BTService_PlayerLocation
  3. BTTask_ClearBlackboardValue
  4. BTTask_Shoot
  위의 4개의 코드가 비헤이비어 트리와 블랙보드를 구성하는 커스텀 태스크와 서비스
  ```
### Character
- 플레이어 캐릭터와 적 캐릭터 모두 ```ShooterCharacter.cpp```의 동일한 구현.
- 플레이어 캐릭터는 ```ShooterPlayerController.cpp```의 구현에 따라 플레이어의 입력에 따른 움직임을 수행
- 적 캐릭터는 ```ShooterAIContoller.cpp```의 구현에 따라 언리얼 비헤이비어 트리의 구현에 따른 움직임을 수행
- 다음과 같은 계층 구조를 따름
  ```
  ShooterCharacter
  |- Gun
  |  |- Projectile

### Others
- 강의에서 제공하는 애셋을 이용
- 언리얼 C++을 기반으로 구현을 진행하였으며, 블루프린트가 더욱 용이한 부분(UMG)에서는 블루프린트를 사용함
  - C++(80%) : Blueprint(20%)

<br/>
<br/>
 
## 프리뷰 🎮
https://github.com/study-kim7507/basic_unreal_SimpleShooter/assets/63442832/e61cde93-0381-43ac-9a1b-ee9be58622d0

<br/>
<br/>
 
## 플랜
1. "좀비 아포칼립스 세상에서 몰려오는 좀비로부터 다양한 장비를 사용하여 오래 생존하는 게임"이라는 아이디어를 바탕으로 한 게임 제작
2. 더욱 섬세한 행동을 하도록 강화학습을 이용한 캐릭터 구현, 더 나은 FPS 게임 제작 (2024. 03 ~ 현재)


