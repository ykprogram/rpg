#include "DxLib.h"
#include "KeyBoard.h"

static short m_Key[256];  // �L�[�̓��͏�Ԋi�[�p�ϐ�

// �L�[�̓��͏�ԍX�V(�Ԃ����Ⴏ������g���̂�main�֐��������ł�k)
void AllKey(){
	char tmpKey[256];             // ���݂̃L�[�̓��͏�Ԃ��i�[����
	GetHitKeyStateAll( tmpKey );  // �S�ẴL�[�̓��͏�Ԃ𓾂�
	// i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�������Z������Ă��Ȃ���� 0�ɂ���
	for( int i=0; i<256; i++ )( tmpKey[i] != 0 ) ? m_Key[i]++ : m_Key[i] = 0;
}

// CheckHitKey�̉������ςȂ����o���Ȃ��֐�,KeyCode�̃L�[�̓��͏�Ԃ��擾����
int CheckHitKey2( int KeyCode ){
	return m_Key[ KeyCode ]; // KeyCode�̓��͏�Ԃ�Ԃ�
} 