int CT1ExcecuteTinyUnit::do_execute(){
    if(m_decode_unit.get_opcode()==MOV3){
        unsigned int reg_n = m_decode_unit.get_op1();
                 int data = m_decode_unit.get_op2();

        m_regs.write_on_reg(reg_n, data);
        m_regs.set_PC( m_regs.get_PC() + 1 );

        return clks[MOV3];
    }

    else if(m_decode_unit.get_opcode()==ADD){
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2() >> 4) & 0xF;

        int Rn = m_regs.read_from_reg(reg_n);
        int Rm = m_regs.read_from_reg(reg_m);
        
        Rn = Rn + Rm;
        m_regs.write_on_reg(reg_n, Rn);
        m_regs.set_PC( m_regs.get_PC() + 1 );
        return clks[ADD];
    }
    else if(m_decode_unit.get_opcode()==SUB){
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2() >> 4) & 0xF;

        int Rn = m_regs.read_from_reg(reg_n);
        int Rm = m_regs.read_from_reg(reg_m);
        
        Rn = Rn - Rm;
        m_regs.write_on_reg(reg_n, Rn);
        m_regs.set_PC( m_regs.get_PC() + 1 );
        return clks[SUB];

    }
    else if(m_decode_unit.get_decode()==MUL){
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2()>>4)&0xF;
                 int Rn = m_regs.read_from_reg(reg_n);
                 int Rm = m_regs.read_from_reg(reg_m);
                 
                 Rn = Rn*Rm;

                 m_regs.write_on_reg(reg_n, Rn);
                 m_regs.set_PC( m_regs.get_PC() + 1 );

                 return clks[MUL];
    }
    else if(m_decode_unit.get_opcode()==MOV0){
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int mem_addr = m_decode_unit.get_op2()&0xFF;
        
        int memory_data = m_mems.read_from_memory(mem_addr);
        m_regs.write_on_reg(reg_n, memory_data);

        m_regs.set_PC( m_regs.get_PC() + 1 );

        return clks[MOV0];
    }

    else if(m_decode_unit.get_opcode()==MOV1){
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int mem_addr = m_decode_unit.get_op2() & 0xFF;
        
        int Rn = m_regs.read_from_reg(reg_n);
        m_mems.write_on_memory(mem_addr,Rn);
        m_regs.set_PC( m_reg.get_PC() + 1 );

        return clks [MOV1];
    }
    else if(m_decode_unit.get_opcode()==MOV2){
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = m_decode_unit.get_op2() & 0xF;
                 int Rn = m_regs.read_from_reg(reg_n);
                 int Rm = m_regs.read_from_reg(reg_m);
        m_mems.write_on_memory(Rn, Rm);

        m_regs.set_PC( get_PC() + 1 );
        
        return clks[MOV2];
    }
    else if(m_decode_unit.get_opcode()==MOV4){
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2()>>4)&0xF;
                 int Rm = m_regs.read_from_reg(reg_m);

                 m_regs.write_on_reg(reg_n,Rm);
                 m_regs.set_PC( m_regs.get_PC() + 1 );

                 return clks[MOOV4];
    }
    else if(m_decode_unit.get_opcode()==MOV5){
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2())&0xF;
                 int Rm = m_regs.read_from_reg(reg_m);
        int Mem_data = m_mems.read_from_memory(Rm);

        m_regs.write_on_reg(reg_n, Mem_data);

        m_regs.set_PC(m_regs.get_PC() + 1 );

        return clks[MOV5];
    }
    else if(m_decode_unit.get_opcode()==JZ){
        unsigned int reg_n = m_decode_unit.get_op1();
                 int Rn = m_regs.read_from_reg(reg_n);
                 int offset = m_decode_unit.get_op2();

                 m_regs.set_PC( m_regs.get_PC() + 1 );
                 
                 if(Rn==0){
                    int pc = m_regs.get_PC();
                    m_regs.set_PC( pc + offset );
                 }
                 
                 return clks[JZ];
    }

}





main.cpp


int main(int argc, char* argv[]){
    if(argc != 3){
        cout << "tpu <input file> <line> \n";
        return -1;
    }

    CFlash1KWord code_memory(argv[1], atoi(argv[2]));
    for (int i=0; i<atoi(argv[2]); i++){
        cout << code_memory.code_at(i) << endl;
    
    }

    int size = atoi(argv[2]);
    int total_clks=0;

    while( regs.get_PC() < size ) {
    
        decode.do_fetch_from(regs.get_PC());
        decode.do_decode();
        decode.show_instruction();

        total_clks += execute.do.execute();
    
    
    }


    regs.show_reg();
    mems.show_mems(0, 50);
}
