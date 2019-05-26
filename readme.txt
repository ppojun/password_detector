// Server 에서 Password 와 Detector의 수를 정하고, Client 에서 Password에 대한 Detect를 시도합니다. 이때, Password Length가 4라면 Client가 2명인 경우, 각각의 Client는 1~2자리까지, Client 2는 3~4자리까지 Detect 시도합니다. 비밀번호를 탐지하면 성공했다는 화면을 display 하는 것이 본 프로그램의 전체적인 흐름입니다.

// password를 여러개의 client에서 나눠서 추적하는 프로그램