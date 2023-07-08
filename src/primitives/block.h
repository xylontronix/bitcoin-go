package main

import (
	"encoding/hex"
	"fmt"
	"time"
)

type Hash [32]byte

type CBlockHeader struct {
	NVersion       int32
	HashPrevBlock  Hash
	HashMerkleRoot Hash
	NTime          uint32
	NBits          uint32
	NNonce         uint32
}

func (header CBlockHeader) SetNull() {
	header.NVersion = 0
	header.HashPrevBlock = Hash{}
	header.HashMerkleRoot = Hash{}
	header.NTime = 0
	header.NBits = 0
	header.NNonce = 0
}

func (header CBlockHeader) IsNull() bool {
	return header.NBits == 0
}

type CBlock struct {
	CBlockHeader
	Vtx      []*CTransactionRef
	FChecked bool
}

func (block CBlock) SetNull() {
	block.CBlockHeader.SetNull()
	block.Vtx = nil
	block.FChecked = false
}

func (block CBlock) GetBlockHeader() CBlockHeader {
	return CBlockHeader{
		NVersion:       block.NVersion,
		HashPrevBlock:  block.HashPrevBlock,
		HashMerkleRoot: block.HashMerkleRoot,
		NTime:          block.NTime,
		NBits:          block.NBits,
		NNonce:         block.NNonce,
	}
}

func (block CBlock) String() string {
	str := fmt.Sprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%d, nBits=%08x, nNonce=%d, vtx=%d)\n",
		block.GetHash().String(),
		block.NVersion,
		block.HashPrevBlock.String(),
		block.HashMerkleRoot.String(),
		block.NTime,
		block.NBits,
		block.NNonce,
		len(block.Vtx),
	)

	for _, tx := range block.Vtx {
		str += "  " + tx.String() + "\n"
	}

	return str
}

type CBlockLocator struct {
	VHave []Hash
}

func (locator CBlockLocator) SetNull() {
	locator.VHave = nil
}

func (locator CBlockLocator) IsNull() bool {
	return len(locator.VHave) == 0
}
