import java.io.*;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ExamRecords implements Comparable<ExamRecords>{
    private ArrayList<Session> studSessions = new ArrayList<>();
    private int recordNumber;
    private String studName;


    public int getRecordNumber() {
        return recordNumber;
    }

    public void setRecordNumber(int recordNumber) {
        this.recordNumber = recordNumber;
    }

    public static double AverageMarkSubject(ArrayList<ExamRecords> list, int sessionNumber, String subject)
    {
        double result = 0;
        for(ExamRecords record : list)
        {
            ExamRecords.Session session = record.getSessionByNumber(sessionNumber);
            int mark = session.getExamMark(subject);
            result += mark;
        }
        result = result / list.size();
        return result;
    }
    public ArrayList<Session> getStudSessions() {
        return studSessions;
    }
    public void setStudSessions(ArrayList<Session> studSessions) {
        this.studSessions = studSessions;
    }
    public String getStudName() {
        return studName;
    }
    public void setStudName(String studName) {
        this.studName = studName;
    }
    public void readGroupSession(BufferedReader br) throws IOException
    {
        this.studName = null;
        String str = br.readLine();
        if(str == null)
            throw new IOException();
        String regex = "\\w+";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str);
        if (!matcher.matches())
            throw new IOException();
        studName = str;
        str = br.readLine();
        regex = "\\d+";
        pattern = Pattern.compile(regex);
        matcher = pattern.matcher(str);
        if (!matcher.matches())
            throw new IOException();
        recordNumber = Integer.parseInt(str);
        while(true)
        {
            try{
                Session session = new Session();
                session.readSession(br);
                studSessions.add(session);
            }
            catch(IOException e)
            {
                break;
            }

        }
    }
    @Override
    public String toString() {
        String str = studName + "\n";
        str += recordNumber + "\n";
        for(int i = 0; i < studSessions.size(); i++)
        {
            str += studSessions.get(i) + "\n";
        }
        return str;
    }
    public Session getSessionByNumber(int number)
    {
        for(Session session: studSessions)
        {
            if(Objects.equals(session.getSessionNumber(), Integer.toString(number)))
            {
                return session;
            }
        }
        return null;
    }
    public void findExcellentStudent()
    {
        ArrayList<Short> arrayList = new ArrayList<>();
        String str = "The Excellent Students:\n";
        for(short i = 0; i < studSessions.size(); i++)
        {
            boolean flag = true;
            for(short j = 0; j < studSessions.get(i).getAllExams().size(); j++)
            {
                if(studSessions.get(i).getAllExams().get(j).getAverageMark() < 9)
                    flag = false;
            }
            if(flag)
            {
                arrayList.add(i);
                str += studSessions.get(i).getStudName()+ " with index:" + i + "\n";
            }
        }
        if(arrayList.isEmpty())
        {
            System.out.println("No Excellent students in this group(");
        }
        else
        {
            System.out.println(str);
        }
    }

    @Override
    public int compareTo(ExamRecords o) {
        return (this.recordNumber - o.recordNumber);
    }

    public class Session {
        public ArrayList<Exam> allExams = new ArrayList<>();
        private String sessionNumber;
        public ArrayList<Exam> getAllExams() {
            return allExams;
        }
        public void setAllExams(ArrayList<Exam> allExams) {
            this.allExams = allExams;
        }
        public String getStudName() {
            return sessionNumber;
        }
        public void setStudName(String studName) {
            this.sessionNumber = studName;
        }
        public void readSession(BufferedReader br) throws IOException {
            String str = br.readLine();
            if(str == null)
                throw new IOException();
            String regex = "\\w+";
            Pattern pattern = Pattern.compile(regex);
            Matcher matcher = pattern.matcher(str);
            if (!matcher.matches())
                throw new IOException();
            sessionNumber = str;
            while (true) {
                Exam exam = new Exam();
                try {
                    exam.readExam(br);
                } catch (IOException e) {
                    break;
                }
                allExams.add(exam);
            }
        }
        public int getExamMark(String subject)
        {
            for(Exam exam: allExams)
            {
                if(Objects.equals(exam.name, subject))
                    return exam.averageMark;
            }
            return -1;
        }
        @Override
        public String toString() {
            String str = sessionNumber + "\n";
            for (int i = 0; i < allExams.size(); i++)
                str += allExams.get(i) + "\n";

            return str;
        }

        public String getSessionNumber() {
            return sessionNumber;
        }

        public void setSessionNumber(String sessionNumber) {
            this.sessionNumber = sessionNumber;
        }

        public class Exam {
            private short averageMark;
            private String name;
            public void readExam(BufferedReader br) throws IOException {

                String str = br.readLine();
                if (str == null)
                    throw new IOException();
                String regex = "(\\d+)(\\s)(\\w+)";

                Pattern pattern = Pattern.compile(regex);
                Matcher matcher = pattern.matcher(str);

                if (matcher.matches())
                {
                    String s = matcher.group(1);
                    this.averageMark = Short.parseShort(s);
                    this.name = matcher.group(3);
                }
                else
                {
                    throw new IOException();
                }
            }
            public short getAverageMark() {
                return averageMark;
            }
            public void setAverageMark(short averageMark) {
                this.averageMark = averageMark;
            }
            public void setName(String name) {
                this.name = name;
            }
            public String getName() {
                return name;
            }
            @Override
            public String toString() {
                return name + " " + averageMark + " ";
            }
        }
    }
}