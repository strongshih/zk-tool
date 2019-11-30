#include "libsnark/zk_proof_systems/ppzksnark/r1cs_ppzksnark/r1cs_ppzksnark.hpp"
#include "libsnark/common/default_types/r1cs_ppzksnark_pp.hpp"
#include "libsnark/gadgetlib1/pb_variable.hpp"
#include "libsnark/gadgetlib1/gadgets/hashes/sha256/sha256_gadget.hpp"
#include "libff/algebra/curves/alt_bn128/alt_bn128_pp.hpp"
#include "libsnark/gadgetlib1/gadgets/basic_gadgets.hpp"
#include <fstream>
#include <iostream>
#include "utils.hpp"

using namespace libsnark;
using namespace std;

template<typename T>
void writeToFile(string path, T& obj) {
    stringstream ss;
    ss << obj;
    ofstream fh;
    fh.open(path, ios::binary);
    ss.rdbuf()->pubseekpos(0, ios_base::out);
    fh << ss.rdbuf();
    fh.flush();
    fh.close();
}

template<typename T>
T loadFromFile(string path) {
    stringstream ss;
    ifstream fh(path, ios::binary);

    assert(fh.is_open());

    ss << fh.rdbuf();
    fh.close();

    ss.rdbuf()->pubseekpos(0, ios_base::in);

    T obj;
    ss >> obj;

    return obj;
}


void serializeProvingKeyToFile(r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> pk, const char* pk_path){
	writeToFile(pk_path, pk);
}

r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> deserializeProvingKeyFromFile(const char* pk_path){
	return loadFromFile<r1cs_ppzksnark_proving_key<default_r1cs_ppzksnark_pp> >(pk_path);
}

void serializeVerifyKeyToFile(r1cs_ppzksnark_verification_key<default_r1cs_ppzksnark_pp> vk, const char* vk_path){
	writeToFile(vk_path, vk);
}

r1cs_ppzksnark_verification_key<default_r1cs_ppzksnark_pp> deserializeVerifyKeyFromFile(const char* vk_path){
	return loadFromFile<r1cs_ppzksnark_verification_key<default_r1cs_ppzksnark_pp> >(vk_path);
}

void serializeProofToFile(r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> proof, const char* proof_path){
	writeToFile(proof_path, proof);
}

r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> deserializeProofFromFile(const char* proof_path){
	return loadFromFile<r1cs_ppzksnark_proof<default_r1cs_ppzksnark_pp> >(proof_path);
}

