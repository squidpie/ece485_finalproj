module LRUStateMachine(Reset, Access, Way, Lru);
    input Reset;
    input Access;
    input [1:0] Way;
    output [1:0] Lru;

    reg [1:0] Lru;

    //0:5 ordering better matches design notes
    reg[0:5] State;

    //Define reset state (LRU 0123 MRU)
    parameter ResetState = 6'b000000;

    //Update state on rising edge of Access
    always @(posedge Access or posedge Reset)
    begin
        if(Reset)
            State <= ResetState;
        else
        begin
            //Update state bits based on accessed way
            if(Way == 2'b00)
            begin
                State[0] <= 1;
                State[1] <= 1;
                State[2] <= 1;
            end
            else if(Way == 2'b01)
            begin
                State[0] <= 0;
                State[3] <= 1;
                State[4] <= 1;
            end
            else if(Way == 2'b10)
            begin
                State[1] <= 0;
                State[3] <= 0;
                State[5] <= 1;
            end
            else
            begin
                State[2] <= 0;
                State[4] <= 0;
                State[5] <= 0;
            end
        end
    end

    //Update output when state changes
    always @(State)
    begin
        if({State[0], State[1], State[2]} == 3'b000)
            Lru = 2'b00;
        else if({State[0], State[3], State[4]} == 3'b100)
            Lru = 2'b01;
        else if({State[1], State[3], State[5]} == 3'b110)
            Lru = 3'b10;
        else if({State[2], State[4], State[5]} == 3'b111)
            Lru = 3'b11;
        else
            $error("Invalid state encountered when generating output");
    end

endmodule


    
