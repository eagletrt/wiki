# Configuring of the CAN-bus on ST MCUs

## On CubeMX
- Connectivity
    - CAN: Activated
    - Bit timing parameters (http://www.bittiming.can-wiki.info/)
        - Prescaler
        - TQ1
        - TQ2
    - NVIC: impisa tuto
- Generate

## In Your Code

#### Activate Notifications

#### Register Callbacks

#### Activate and Configure the Hardware Filters
When a new message is received, CAN nodes can use hardware filters to decide if the message must be copied into SRAM and trigger an IRQ, or if it has to be discarded. The advantage of hardware filters is that unwanted messages don't waste any CPU cycles thus saving potentially a lot of resources, especially on heavy traffic networks with many nodes.

STMs are equipped with a number of filter banks, each of which is composed by two 32-bit registers. Each bank can operate in **ID Mask Mode** or in **ID List Mode**: in the former, one register acts as the mask and the second as the ID, while in the latter mode, both registers represent IDs of the list. Filter banks can also be configured to operate in 16-bit mode, therefore doubling their capacity (four 16-bit registers instead of two 32-bit registers, which are split in two). In ID Mask mode this yields two pairs of Mask+ID, while in ID List mode, of course, it yields 4 ID registers.

For a better understanding of the layout of a filter bank in relation to hardware registers, refer to the image below.

![CAN Filter register](imgs/can-filters.png)

##### ID Mask Mode
In this mode the filtering is based on a mask register which tells which bits of the ID register need to be compared with the incoming message ID. For instance, with a mask of `11110000000` and an ID of `01110000000`, only messages whose ID begins with `0111` (`0x3`) will be accepted. Some more examples follow.

!!! example
    - Mask: `0b11111111111` (`0x03FF`) <br/>
      ID: `0b11111111111` (`0x03FF`) <br/>
      Accepted: only ID == `0x03FF`

    - Mask: `0b11111111110` (`0x03FE`) <br/>
      ID: `0b11111111110` (`0x03FE`) <br/>
      Accepted: {`0x03FE`, `0x03FF`} (as bit 0 of the filter is disabled)

     - Mask: `0b11111111000` (`0x03F8`) <br/>
       ID: `0b00000000000` (`0x0000`) <br/>
       Accepted: ID from `0x000` to `0x007` (as bits 0, 1, 2 of the filter are disabled)

##### ID List Mode
In ID List Mode, incoming messages' IDs are simply compared for equality with every element of the list.

##### Code
To configure a filter, you need to allocate and populate a `CAN_FilterTypeDef` struct and pass it by reference to `HAL_CAN_ConfigFilter(...)`. Its fields are the following:

- `FilterMode`: either `CAN_FILTERMODE_IDMASK` or `CAN_FILTERMODE_IDLIST`, for the respective modes
- `FilterIdHigh`: MSBs of the ID register (or first one of the two 16-bit registers)
- `FilterIdLow`: LSBs of the ID register (or second one of the two 16-bit registers)
- `FilterMaskIdHigh`: MSBs of the Mask register (or first one of the two 16-bit registers)
- `FilterMaskIdLow`: LSBs of the Mask register (or second one of the two 16-bit registers)
- `FilterFIFOAssignment`: the queue in which to store messages (a value of CAN_filet_FIFO, e.g. `CAN_FILTER_FIFO0`)
- `FilterBank`: index of the filter bank to be initialized
- `FilterScale`: `CAN_FILTERSCALE_16BIT` or `CAN_FILTERSCALE_32BIT`, for the respective register scale
- `FilterActivation`: `ENABLE` or `DISABLE`

!!! example
    A filter that accepts everything would look like this:

    ```C
    CAN_FilterTypeDef f;
    f.FilterMode = CAN_FILTERMODE_IDMASK;
    f.FilterIdLow = 0x0;    // Meaningless, mask is all 0s
    f.FilterIdHigh = 0x0; // Meaningless, mask is all 0s
    f.FilterMaskIdHigh = 0x0;
    f.FilterMaskIdLow = 0x0;
    f.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    f.FilterBank = 0;
    f.FilterScale = CAN_FILTERSCALE_32BIT;
    f.FilterActivation = ENABLE;

    HAL_CAN_ConfigFilter(hcan, &f);
    ```

#### HAL_CAN_Start
