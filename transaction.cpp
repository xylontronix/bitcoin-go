```go
package main

import (
	"encoding/hex"
	"fmt"
	"strconv"
)

type Hash [32]byte

func (h Hash) String() string {
	return hex.EncodeToString(h[:10])
}

type OutPoint struct {
	Hash  Hash
	Index uint32
}

func (o OutPoint) String() string {
	return fmt.Sprintf("COutPoint(%s, %d)", o.Hash.String(), o.Index)
}

type Script []byte

type TxIn struct {
	PrevOut   OutPoint
	ScriptSig Script
	Sequence  uint32
}

func NewTxIn(prevOutHash Hash, prevOutIndex uint32, scriptSig Script, sequence uint32) TxIn {
	return TxIn{
		PrevOut:   OutPoint{Hash: prevOutHash, Index: prevOutIndex},
		ScriptSig: scriptSig,
		Sequence:  sequence,
	}
}

func (in TxIn) String() string {
	str := "CTxIn("
	str += in.PrevOut.String()

	if in.PrevOut.Hash == [32]byte{} {
		str += fmt.Sprintf(", coinbase %s", hex.EncodeToString(in.ScriptSig))
	} else {
		str += fmt.Sprintf(", scriptSig=%s", hex.EncodeToString(in.ScriptSig[:24]))
	}

	if in.Sequence != 0xFFFFFFFF {
		str += fmt.Sprintf(", nSequence=%d", in.Sequence)
	}

	str += ")"
	return str
}

type TxOut struct {
	Value        int64
	ScriptPubKey Script
}

func NewTxOut(value int64, scriptPubKey Script) TxOut {
	return TxOut{
		Value:        value,
		ScriptPubKey: scriptPubKey,
	}
}

func (out TxOut) String() string {
	return fmt.Sprintf("CTxOut(nValue=%d.%08d, scriptPubKey=%s)", out.Value/100000000, out.Value%100000000, hex.EncodeToString(out.ScriptPubKey[:30]))
}

type MutableTransaction struct {
	Version  int32
	LockTime uint32
	TxIn     []TxIn
	TxOut    []TxOut
}

func NewMutableTransaction() MutableTransaction {
	return MutableTransaction{
		Version:  CTransactionCurrentVersion,
		LockTime: 0,
	}
}

func NewMutableTransactionFromTransaction(tx Transaction) MutableTransaction {
	return MutableTransaction{
		Version:  tx.Version,
		LockTime: tx.LockTime,
		TxIn:     tx.TxIn,
		TxOut:    tx.TxOut,
	}
}

func (tx MutableTransaction) GetHash() Hash {
	serialized := Serialize(tx)
	return Hash(Sha256d(serialized))
}

type Transaction struct {
	Version      int32
	LockTime     uint32
	TxIn         []TxIn
	TxOut        []TxOut
	Hash         Hash
	WitnessHash  Hash
}

const (
	CTransactionCurrentVersion = 1
)

func NewTransactionFromMutable(tx MutableTransaction) Transaction {
	hash := tx.GetHash()
	witnessHash := hash
	return Transaction{
		Version:      tx.Version,
		LockTime:     tx.LockTime,
		TxIn:         tx.TxIn,
		TxOut:        tx.TxOut,
		Hash:         hash,
		WitnessHash:  witnessHash,
	}
}

func (tx Transaction) GetValueOut() int64 {
	var valueOut int64
	for _, txOut := range tx.TxOut {
		if !MoneyRange(txOut.Value) || !MoneyRange(valueOut+txOut.Value) {
			panic("value out of range")
		}
		valueOut += txOut.Value
	}
	if !MoneyRange(valueOut) {
		panic("value out of range")
	}
	return valueOut
}

func (tx Transaction) GetTotalSize() int {
	serialized := Serialize(tx)
	return len(serialized)
}

func (tx Transaction) String() string {
	str := fmt.Sprintf("CTransaction(hash=%s, ver=%d, vin.size=%d, vout.size=%d, nLockTime=%d)\n",
		tx.Hash.String(), tx.Version, len(tx.TxIn), len(tx.TxOut), tx.LockTime)

	for _, txIn := range tx.TxIn {
		str += "    " + txIn.String() + "\n"
	}

	for _, txOut := range tx.TxOut {
		str += "    " + txOut.String() + "\n"
	}

	return str
}

func MoneyRange(value int64) bool {
	return value >= 0 && value <= 2100000000000000
}

func Sha256d(data []byte) []byte {
	// Your implementation of double SHA-256 hash function goes here
	return nil
}

func Serialize(tx MutableTransaction) []byte {
	// Your implementation of serialization goes here
	return nil
}
```
