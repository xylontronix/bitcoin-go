package main

import (
	"encoding/hex"
	"fmt"
	"strings"
)

type Hash [32]byte

func (h Hash) String() string {
	return hex.EncodeToString(h[:])
}

type BlockHeader struct {
	Version       int32
	PrevBlockHash Hash
	MerkleRoot    Hash
	Timestamp     uint32
	Bits          uint32
	Nonce         uint32
}

func (header BlockHeader) GetHash() Hash {
	serialized := Serialize(header)
	return Hash(Sha256d(serialized))
}

type Block struct {
	Header BlockHeader
	Tx     []*Transaction
}

func (block Block) String() string {
	var sb strings.Builder

	sb.WriteString(fmt.Sprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%d, nBits=%08x, nNonce=%d, vtx=%d)\n",
		block.Header.GetHash().String(),
		block.Header.Version,
		block.Header.PrevBlockHash.String(),
		block.Header.MerkleRoot.String(),
		block.Header.Timestamp,
		block.Header.Bits,
		block.Header.Nonce,
		len(block.Tx),
	))

	for _, tx := range block.Tx {
		sb.WriteString("  " + tx.String() + "\n")
	}

	return sb.String()
}

func Sha256d(data []byte) []byte {
	// Your implementation of double SHA-256 hash function goes here
	return nil
}

func Serialize(header BlockHeader) []byte {
	// Your implementation of serialization goes here
	return nil
}
