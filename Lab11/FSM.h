#pragma once
#include <vector>
#include <iostream>


namespace louie
{
	typedef unsigned int UINT;

	class FSM
	{
	private:
		// ������, ��������� �� �����:
		//			������	  �������	   ������� ��������� ��� ��������	
		std::vector<std::pair<std::string, std::vector<int>>> transitions_;
		
		// ��������� ��������, ��� ������� ������������ ��������� �������
		std::vector<int> sample_states_;

		// ������� ��������� ��������
		UINT state_;
	
		// ������� ������� �������� �������, �.�. ������� ���������
		void PrepareTabel(std::vector<std::string> samples, std::vector<char> alphabet);

		// ������� ������ ��������� ��������
		void ChangeState(char symbol, std::vector<char>& alphabet);
	public:
		// ������� FindOneSample ���������� ������, ������� ��������� �� ���������
		// ��������� ���� � ������ (������� ����)
		std::vector<int> FindOneSample(std::string sample, std::string file_path, bool print = false);

		// ������� FindSamples ���������� ����: ������� � ������, ������� ��������� �� ���������
		// ��������� ���� � ������ (�������� ������ ������)
		std::vector<std::pair<std::string, std::vector<int>>>
			FindSamples(std::vector<std::string> samples, std::string file_path, bool print = false);
	};
}