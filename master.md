### 3.1. Motivation for Account Abstraction

#### 3.1.1. Why is there a need for account abstraction?

###### Key pain points such as private key management, transaction fees, usability barriers, and security vulnerabilities.

#### 3.1.2. Account Abstraction Overview

###### Account abstraction allows smart contract logic to manage not only transaction effects but also fee payment and validation processes.

###### Key benefits include:

-   Support for multisig wallets.
-   Smart recovery mechanisms (e.g., social recovery wallets).
-   Flexibility in changing keys without altering wallets.
-   Enhanced security (e.g., quantum safety).

#### 3.1.3. Historical Development & Proposals

###### Multiple approaches to account abstraction have been explored, such as:

-   EIP-86 (early attempt to introduce account abstraction but wasn't adopted).
-   EIP-2938 (proposal for "native" in-protocol abstraction, but not yet fully implemented).
-   ERC-4337 (alternative approach that doesn't require protocol changes, focuses on off-chain mechanisms).

#### 3.1.4. Understanding Blockchain Accounts

###### Limitations of Current Blockchain Accounts

-   Externally Owned Accounts (EOAs): Controlled by private keys, with limited flexibility and security features.
-   Smart Contract Accounts: More programmable but less commonly used for everyday transactions.

#### 3.1.5. Motivation for Account Abstraction

###### Challenges with EOAs

-   Key Management: Risk of key loss or theft.
-   High Fees: Unpredictable transaction costs.
-   Complexity: Non-technical users face difficulty in managing private keys and performing transactions.
-   Security Risks: No built-in support for multisig or recovery options.

###### Why Account Abstraction is Needed

-   Better User Experience: Easier and more flexible wallet management.
-   Improved Security: Features like multisig, social recovery, and quantum resistance.
-   Increased Flexibility: Ability to change keys and define custom fee structures without creating a new wallet.

### 3.2. what is aa().

#### 3.2.1. UserOperation

###### Definition:

-   A UserOperation (UO) is an off-chain object that defines a transaction initiated by a user via a smart contract wallet.
-   UOs replace traditional transactions by encapsulating the transaction details (e.g., calldata, gas price, nonce) in a standardized form.

###### Structure of a UserOperation

-   Fields: sender, nonce, initCode, callData, callGas, verificationGas, preVerificationGas, maxFeePerGas, paymasterAndData.
-   Custom validation logic: the smart contract defines how to validate the UO before it is accepted and included in the blockchain.

###### Differences from Regular Transactions

-   UserOperations contain the logic for verification and execution of a transaction in a decentralized way (via bundlers and validators).

#### 3.2.2. Bundlers

##### Role of Bundlers

-   Bundlers collect multiple UserOperations, package them, and submit them to the blockchain in the form of a single transaction.
-   The bundler acts like a miner but specifically for UserOperations.
-   Bundlers are responsible for:

    -   Filtering UserOperations based on their fee payment ability.
    -   Ensuring the validity of each operation before inclusion in a block.

###### Bundling Process:

-   UserOperations are stored in a mempool.
-   Bundlers pick a batch of UOs, perform validations (e.g., fee checks, gas limits), and execute them.
-   Bundlers are paid in fees, ensuring they process only UOs with valid gas payments.

#### 3.2.3. Mempool

###### Separate Mempool for UserOperations

-   Unlike EOAs, UserOperations are stored in a dedicated mempool for Account Abstraction transactions.
-   Nodes participating in Account Abstraction maintain this separate mempool for UOs.

###### Mempool Operations

-   Validation before propagation: Nodes verify UserOperations to ensure they are valid and contain the necessary gas fees before sharing them.
-   Optimizing mempool congestion: The dedicated mempool for UserOperations ensures regular transactions do not interfere with AA-related operations.

###### Interaction with Builders:

-   Builders (and bundlers) are connected to this mempool to include UOs in blocks, similar to how regular transactions are handled by miners.

### 3.3. Detailed Architecture of Account Abstraction (ERC-4337)

#### 3.3.1. User Operations Pipeline

###### User Wallet

-   The user interacts with a smart contract wallet, defining the transaction logic, including fee payment, gas management, and signature validation.

###### Off-Chain UserOperation Creation

-   The user generates a UserOperation that includes details like the contract address, calldata, and gas parameters.
-   The UserOperation is broadcast to the dedicated UserOperation mempool.

#### 3.3.2. Bundling and Execution

###### Bundler Validation

-   A bundler collects multiple UserOperations from the mempool, checking

    -   Fee sufficiency: Does the UO have enough gas fees to cover execution?

    -   Validation logic: Are the custom rules for transaction verification met (e.g., multisig, time delays)?

-   Bundlers validate UserOperations by interacting with the contract logic in the UO.

#### 3.3.3. Inclusion in Block

###### After validation, the bundler submits the batch of UOs as a single transaction on-chain.

###### On-chain smart contracts execute the UserOperations, managing gas and state changes.

#### 3.3.4. Security and Censorship Resistance

###### Customizable Validation Logic

-   Account Abstraction introduces the ability to define custom signature and transaction validation logic.
-   This makes AA wallets more flexible (e.g., multisig, quantum-safe signatures), but also adds complexity in validation.

###### Censorship Resistance

-   CRLists and DoS Resistance
    -   Future proposals include CRLists (Commit-Root Lists) to prevent bundlers from censoring UserOperations by ensuring valid UOs are included in the block if they meet the gas fee requirements.
-   AA in Rollups and L2s:
    -   Account Abstraction can be further integrated into Layer 2 (L2) rollups, reducing costs and improving censorship resistance.

### 3.3. What is recovery solution.

-   `Off-chain backup and recovery`: simply store sk into a secure and available backup space and can recover it on demand.
-   `Use of seed phrases`: is a random user-friendly words that users can store more easily than original sk. Similarly sk, a seed phrase must be stored in a safe space because anyone who successfully accesses a seed phrase afford to regain the private key.
-   `Pre-signed transactions`: are transactions that send some or all assets to a secondary account. Users pre-sign and store them in offline mediums. Users can execute the transactions when they lose their keys and recover their account's funds. However, users must pay attention to managing secondary account.
-   `Smart contract recovery through guardians`: use the power of smart contract to recover the access. Users pick some others to help them recover accounts if necessary. They, who refer to guardians, only can help users perform account recovery when needed, but without having any powers such as signing messages or spending funds. After users create a new (pk, sk) pair, smart contract enables guardians to perform the special operation, it changes the ownership into the new key pair.
-   `Smart contract guardian-less recovery`: use the power of smart contract likely to guardians but don't need to involve guardian.

---> some comparison between five recovery solutions.

### 3.4. The combination between AA and recovery solution
