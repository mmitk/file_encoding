#include "LFSR/LFSR.hpp"
#include <string>
#include <memory>
enum filetype{image, sound, text};
class EncObj{
   public:
	explicit public EncObj:string filename(_filename), filetype f(_f){};
   private:
	string _password;
	string _filename;
	filetype _f;
	unique_ptr<LFSR> lin_feed;

};
