package main

import (
	"encoding/hex"
	"fmt"
)

type Hash [32]byte

type COutPoint struct {
	Hash Hash
	N    uint32
}

const NullIndex = ^uint32(0)

func (outpoint COutPoint) SetNull() {
	outpoint.Hash = Hash{}
	outpoint.N = NullIndex
}

func (outpoint COutPoint) IsNull() bool {
	return outpoint.Hash == Hash{} && outpoint.N == NullIndex
}

type CTxIn struct {
	PrevOut     COutPoint
	ScriptSig   CScript
	NSequence   uint32
	ScriptWitness CScriptWitness
}

type CTxOut struct {
	NValue       CAmount
	ScriptPubKey CScript
}

type CTransaction struct {
	Vin       []CTxIn
	Vout      []CTxOut
	NVersion  int32
	NLockTime uint32
	Hash      Hash
	WitnessHash Hash
}

type CMutableTransaction struct {
	Vin       []CTxIn
	Vout      []CTxOut
	NVersion  int32
	NLockTime uint32
}

func (tx CTransaction) IsNull() bool {
	return len(tx.Vin) == 0 && len(tx.Vout) == 0
}

func (tx CTransaction) GetHash() Hash {
	return tx.Hash
}

func (tx CTransaction) GetWitnessHash() Hash {
	return tx.WitnessHash
}

func (tx CTransaction) GetValueOut() CAmount {
	total := CAmount(0)
	for _, txout := range tx.Vout {
		total += txout.NValue
	}
	return total
}

func (tx CTransaction) GetTotalSize() unsigned int {
	// Calculate the total size of the transaction
	totalSize := len(SerializeTransaction(tx))
	return unsigned(totalSize)
}

func (tx CTransaction) IsCoinBase() bool {
	return len(tx.Vin) == 1 && tx.Vin[0].PrevOut.IsNull()
}

func (tx CTransaction) String() string {
	str := fmt.Sprintf("CTransaction(hash=%s, ver=%d, vin.size=%d, vout.size=%d, nLockTime=%d)\n",
		tx.GetHash().String()[:10],
		tx.NVersion,
		len(tx.Vin),
		len(tx.Vout),
		tx.NLockTime,
	)

	for _, txin := range tx.Vin {
		str += "    " + txin.String() + "\n"
	}

	for _, txout := range tx.Vout {
		str += "    " + txout.String() + "\n"
	}

	return str
}

func (tx CTxIn) String() string {
	str := "CTxIn("
	str += tx.PrevOut.String()
	if tx.PrevOut.IsNull() {
		str += fmt.Sprintf(", coinbase %s", hex.EncodeToString(tx.ScriptSig))
	} else {
		str += fmt.Sprintf(", scriptSig=%s", hex.EncodeToString(tx.ScriptSig)[:24])
	}
	if tx.NSequence != SEQUENCE_FINAL {
		str += fmt.Sprintf(", nSequence=%d", tx.NSequence)
	}
	str += ")"
	return str
}

func (tx CTxOut) String() string {
	return fmt.Sprintf("CTxOut(nValue=%d.%08d, scriptPubKey=%s)",
		int64(tx.NValue)/COIN,
		int64(tx.NValue)%COIN,
		hex.EncodeToString(tx.ScriptPubKey)[:30],
	)
}

func SerializeTransaction(tx CTransaction) []byte {
	// Your implementation of transaction serialization goes here
	return nil
}

func SerializeTransaction(tx CMutableTransaction) []byte {
	// Your implementation of transaction serialization goes here
	return nil
}

func DeserializeTransaction(data []byte) (CTransaction, error) {
	// Your implementation of transaction deserialization goes here
	return CTransaction{}, nil
}

func DeserializeTransaction(data []byte) (CMutableTransaction, error) {
	// Your implementation of transaction deserialization goes here
	return CMutableTransaction{}, nil
}
