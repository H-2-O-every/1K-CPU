MOV0 Rn M[direct]
int CT1ExecuteTinyUnit::do_execute(){
    if(m_decode_unit.get_opcode()==MOV0){
        unsigned int reg_n = m_decode_unit.get_op1();
                 int reg_m = (m_decode_unit.get_op2())&0xFF;

        int memory_data = m_mems.read_from_memory(reg_m);
        m_regs.write_on_reg(reg_n, memory_data);

        m_regs.set_PC( m_regs.get_PC() + 1 );
    
        return clks[MOV0]; //8
    }

    else if(m_decode_unit.get_opcode() == MOV1){
    //MOV1 M[direct] Rn    
    
    unsigned int reg_n = m_decode_unit.get_op1();
             int reg_m = m_decode_unit.get_op2() &0xFF;

             int Rn = m_regs.read_from_reg(reg_n);

             m_mems.write_on_memory(reg_m, Rn);
            
            m_regs.set_PC( m_regs.get_PC() + 1 );
            return clks[MOV1]; //8
    }

    else if(m_decode_unit.get_opcode()==MOV2){
        //MOV2 M[Rm] Rn
    
        unsigned int reg_n = m_decode_unit.get_op1();
                 int reg_m = m_decode_unit.get_op2() &0xF;
                
                 int Rn = m_regs.read_from_reg(reg_n);
                 int Rm = m_regs.read_from_reg(reg_m);
                 m_mems.write_on_memory(Rm, Rn);
                 m_regs.set_PC( m_regs.get_PC() + 1 );
                 return clks[MOV2]; //12
    }

    else if(m_decode_unit.get_opcode()==MOV3){
        //MOV3 Rn #immed

        unsigned int reg_n = m_decode_unit.get_op1();
                 int data = m_decode_unit.get_op2();

        m_regs.write_on_reg(reg_n, data);

        m_regs.set_PC( m_regs.get_PC() + 1 );

        return clks[MOV3]; //6
    }
    
    else if(m_decode_unit.get_opcode()==ADD){
        //MOV3 Rn Rn+Rm

        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2()>>4)&0xF;

        int Rn = m_regs.read_from_reg(reg_n);
        int Rm = m_regs.read_from_reg(reg_m);
        
        Rn = Rn + Rm;
        m_regs.write_on_reg(reg_n, Rn);
    
        m_regs.set_PC( m_regs.get_PC() + 1 ):
        return clks[ADD]; //4
    
    }


    else if(m_decode_unit.get_opcode() == SUB){
        //SUB Rn Rn-Rm
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2()>>4)&0xF;
                 int Rn = m_regs.read_from_reg(reg_n);
                 int Rm = m_regs.read_from_reg(reg_m);
        
        Rn = Rn - Rm;
        m_regs.write_on_reg(reg_n, Rn);
        m_regs.set_PC( m_regs.get_PC() + 1 );
        return clks[SUB]; //4
    }
    
    else if(m_decode_unit.get_opcode()==JZ){
        //JZ Rn #relative

        unsigned int reg_n = m_decode_unit.get_op1();
                 int offset = m_decode_unit.get_op2();

        int Rn = m_regs.read_from_reg(reg_n);
        
        m_regs.set_PC ( m_regs.get_PC() + 1 );

            if(Rn==0){
                int pc = m_regs.get_PC();
                m_regs.set_PC( pc + offset );
            }

        return clks[JZ]; //12
        
    }

    else if(m_decode_unit.get_opcode()==MUL){
        //MUL Rn Rn*Rm

        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2()>>4)&0xF;
        int Rn = m_regs.read_from_reg(reg_n);
        int Rm = m_regs.read_from_reg(reg_m);
        Rn = Rn*Rm;
        
        m_regs.write_on_reg(reg_n, Rn);
        m_regs.set_PC( m_regs.get_PC() + 1 );
        
        return clks[MUL]; //30
        }

    else if(m_decode_unit.get_opcode()==MOV4){
        //MOV4 Rn Rm
        
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = (m_decode_unit.get_op2()>>4)&0xF;
        
        int Rm = m_regs.read_from_reg(reg_m);

        m_regs.write_on_reg(reg_n, Rm);

        m_regs.set_PC( m_regs.get_PC() + 1 );
        return clks[MOV4]; //2
        }

   else if(m_decode_unit.get_opcode()==MOV5){
        //MOV5 Rn M[Rm]
        unsigned int reg_n = m_decode_unit.get_op1();
        unsigned int reg_m = m_decode_unit.get_op2()&0xF;
                 int Rm = m_regs.read_from_reg(reg_m);
                 int Mem_data = m_mems.read_from_memory(Rm);

                 m_regs.write_on_reg(reg_n, Mem_data);
                 m_regs.set_PC( m_regs.get_PC() + 1 );

                 return clks[MOV5]; //12
       
   }



}
















